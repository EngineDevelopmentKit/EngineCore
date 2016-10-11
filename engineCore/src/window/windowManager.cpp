/**
* @cond ___LICENSE___
*
* Copyright (c) 2016 Koen Visscher, Paul Visscher, Andrew Mac and individual contributors.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
* @endcond
*/

#include "warnings/push.h"
#include "warnings/nonConstRValue.h"

#include "window/windowManager.h"
#include "window/impl/sfmlWindow.h"

#include "manager/eventManager.h"
#include "manager/applicationManager.h"
#include "manager/configurationManager.h"

#include "common/file.h"
#include "common/util.h"

#include "warnings/pop.h"

#include <iostream>

using namespace EDK;

WindowManager::WindowManager()
    : mMainWindow( 0 ),
      mWindowCount( 0 ),
      mCursorVisible( true )
{
}

void WindowManager::OnInit()
{
    //mTitle = GetManagers()->configuration->GetString( "WindowTitle" );
    //mIcon = GetManagers()->configuration->GetString( "IconPath" );
    
    mTitle = "Test window";
    mIcon = "";  
}


void WindowManager::OnPostInit()
{
    Observe< WindowManager, OnWindowCloseEvent>( &WindowManager::OnWindowClose );
}

void WindowManager::OnRelease()
{
    for ( auto it = mWindows.begin(); it != mWindows.end(); ++it )
    {
        IWindow *win = it->second;
        SAFE_RELEASE_DELETE( win );
    }

    mWindows.clear();
}

void WindowManager::OnUpdate()
{
    for ( auto it = mWindows.begin(); it != mWindows.end(); ++it )
    {
        it->second->ProcessEvents();
    }
}

U8 WindowManager::CreateNewWindow( const Vec2I &size, Window::Style style /*= WindowStyle::DEFAULT */ )
{
    std::lock_guard< std::recursive_mutex > lock( mMutex );
    
    const U8 windowID = GetNewID();
    
    // TODO, switch to plugin!
    IWindow *const win = new SFMLWindow( windowID );

    win->Open( size, mTitle, style );
    win->SetIcon( mIcon );
    win->SetCursorVisible( mCursorVisible );

    mWindows[windowID] = win;

    if ( mWindowCount <= 1 )
    {
        SetMainWindow( windowID );
    }

    return windowID;
}

void WindowManager::DestroyWindow( U8 windowID /*= 0*/ )
{
    std::lock_guard< std::recursive_mutex > lock( mMutex );

    --mWindowCount;

    auto it = mWindows.find( windowID );

    if ( it != mWindows.end() )
    {
        IWindow *win = it->second;
        SAFE_RELEASE_DELETE( win );
        mWindows.erase( it );
    }

    mFreeIDs.push( windowID );
}

bool WindowManager::IsValid( U8 windowID /*= 0*/ ) const
{
    std::lock_guard< std::recursive_mutex > lock( mMutex );

    return CheckIsValid( windowID );
}

NativeWindowHandle WindowManager::GetHandle( U8 windowID  /*= 0*/ ) const
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        return mWindows.at( ID )->GetNativeWindowHandle();
    }

    return nullptr;
}

void WindowManager::SetMainWindow( U8 windowID )
{
    std::lock_guard< SpinLock > lock( mMainWindowLock );

    mMainWindow = windowID;
}

U8 WindowManager::GetMainWindow() const
{
    std::lock_guard< SpinLock > lock( mMainWindowLock );

    return mMainWindow;
}

U8 WindowManager::GetWindowCount() const
{
    std::lock_guard< std::recursive_mutex > lock( mMutex );

    return mWindowCount;
}

Vec2I WindowManager::GetSize( U8 windowID /*= 0*/ )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        return mWindows.at( ID )->GetSize();
    }

    return Vec2I( 0, 0 );
}

/*
Vec2I WindowManager::GetClientSize( U8 windowID )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        return mWindows.at( ID )->GetClientSize();
    }

    return Vec2I( 0, 0 );
}
*/

void WindowManager::SetSize( const Vec2I &size, U8 windowID /*= 0*/ )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        mWindows.at( ID )->SetSize( size );
    }
}

Vec2I WindowManager::GetPosition( U8 windowID /*= 0*/ )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        return mWindows.at( ID )->GetPosition();
    }

    return Vec2I( 0, 0 );
}

void WindowManager::SetPosition( const Vec2I &position, U8 windowID /*= 0*/ )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( IsValid( ID ) )
    {
        mWindows.at( ID )->SetPosition( position );
    }
}

void WindowManager::SetCursorVisible( bool visible )
{
    std::lock_guard< std::recursive_mutex > lock( mMutex );

    // prevent useless work
    if ( mCursorVisible != visible )
    {
        mCursorVisible = visible;

        for ( auto it = mWindows.begin(); it != mWindows.end(); ++it )
        {
            if ( it->second )
            {
                it->second->SetCursorVisible( visible );
            }
        }
    }
}

/*
void WindowManager::SetFullScreen( bool fullscreen, U8 windowID  )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        mWindows.at( ID )->SetFullScreenMode( fullscreen );
    }
}
*/

void WindowManager::SetVisible( bool visible, U8 windowID /*= 0*/ )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        mWindows.at( ID )->SetVisible( visible );
    }
}

void WindowManager::SetIcon( const std::string &iconPath )
{
    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( File::Exists( iconPath ) )
    {
        if ( mIcon != iconPath )
        {
            mIcon = iconPath;

            for ( auto it = mWindows.begin(); it != mWindows.end(); ++it )
            {
                if ( it->second )
                {
                    it->second->SetIcon( iconPath );
                }
            }
        }
    }
}

void WindowManager::SetTitle( const std::string &title )
{
    std::lock_guard< std::recursive_mutex > lock( mMutex );

    // prevent useless work
    if ( mTitle != title )
    {
        mTitle = title;

        for ( auto it = mWindows.begin(); it != mWindows.end(); ++it )
        {
            if ( it->second )
            {
                it->second->SetTitle( title );
            }
        }
    }
}

U8 WindowManager::GetNewID()
{
    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( mFreeIDs.size() > 0 )
    {
        const U8 id = mFreeIDs.top();
        mFreeIDs.pop();
        return id;
    }
    else
    {
        return ++mWindowCount;
    }
}

bool WindowManager::CheckIsValid( U8 windowID ) const
{
    return mWindows.find( windowID ) != mWindows.end();
}

void WindowManager::OnWindowClose( const OnWindowCloseEvent &e )
{
    GetManagers()->application->Quit();
}