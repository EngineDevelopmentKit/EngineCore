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

#include "window/abstract/windowEvents.h"
#include "window/sfmlWindowManager.h"
#include "window/sfmlWindow.h"

#include "manager/configurationManager.h"
#include "manager/applicationManager.h"
#include "manager/eventManager.h"

#include "common/file.h"
#include "common/util.h"

#include "warnings/pop.h"

#include <iostream>

using namespace EDK;

SFMLWindowManager::SFMLWindowManager()
    : mMainWindow( 0 ),
      mWindowCount( 0 ),
      mCursorVisible( true )
{
}

void SFMLWindowManager::OnInit()
{
    //mTitle = GetManagers()->configuration->GetString( "WindowTitle" );
    //mIcon = GetManagers()->configuration->GetString( "IconPath" );

    mTitle = "Test window";
    mIcon = "";
}


void SFMLWindowManager::OnPostInit()
{
    Observe< SFMLWindowManager, OnWindowCloseEvent>( &SFMLWindowManager::OnWindowClose );
}

void SFMLWindowManager::OnRelease()
{
    for ( auto it = mWindows.begin(); it != mWindows.end(); ++it )
    {
        IWindow *win = it->second;
        SAFE_RELEASE_DELETE( win );
    }

    Unobserve< SFMLWindowManager, OnWindowCloseEvent>( &SFMLWindowManager::OnWindowClose );

    mWindows.clear();
}

void SFMLWindowManager::OnUpdate()
{
    for ( auto it = mWindows.begin(); it != mWindows.end(); ++it )
    {
        it->second->ProcessEvents();
    }
}

U8 SFMLWindowManager::CreateNewWindow( const Vec2I &size, Window::Style style /*= WindowStyle::DEFAULT */ )
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

void SFMLWindowManager::DestroyWindow( U8 windowID /*= 0*/ )
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

bool SFMLWindowManager::IsValid( U8 windowID /*= 0*/ ) const
{
    std::lock_guard< std::recursive_mutex > lock( mMutex );

    return CheckIsValid( windowID );
}

NativeWindowHandle SFMLWindowManager::GetHandle( U8 windowID  /*= 0*/ ) const
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        return mWindows.at( ID )->GetNativeWindowHandle();
    }

    return WindowHandleNull;
}

void SFMLWindowManager::SetMainWindow( U8 windowID )
{
    std::lock_guard< SpinLock > lock( mMainWindowLock );

    mMainWindow = windowID;
}

U8 SFMLWindowManager::GetMainWindow() const
{
    std::lock_guard< SpinLock > lock( mMainWindowLock );

    return mMainWindow;
}

U8 SFMLWindowManager::GetWindowCount() const
{
    std::lock_guard< std::recursive_mutex > lock( mMutex );

    return mWindowCount;
}

Vec2I SFMLWindowManager::GetSize( U8 windowID /*= 0*/ )
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
Vec2I SFMLWindowManager::GetClientSize( U8 windowID )
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

void SFMLWindowManager::SetSize( const Vec2I &size, U8 windowID /*= 0*/ )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        mWindows.at( ID )->SetSize( size );
    }
}

Vec2I SFMLWindowManager::GetPosition( U8 windowID /*= 0*/ )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        return mWindows.at( ID )->GetPosition();
    }

    return Vec2I( 0, 0 );
}

void SFMLWindowManager::SetPosition( const Vec2I &position, U8 windowID /*= 0*/ )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( IsValid( ID ) )
    {
        mWindows.at( ID )->SetPosition( position );
    }
}

void SFMLWindowManager::SetCursorVisible( bool visible )
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
void SFMLWindowManager::SetFullScreen( bool fullscreen, U8 windowID  )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        mWindows.at( ID )->SetFullScreenMode( fullscreen );
    }
}
*/

void SFMLWindowManager::SetVisible( bool visible, U8 windowID /*= 0*/ )
{
    const U8 ID = windowID == 0 ? GetMainWindow() : windowID;

    std::lock_guard< std::recursive_mutex > lock( mMutex );

    if ( CheckIsValid( ID ) )
    {
        mWindows.at( ID )->SetVisible( visible );
    }
}

void SFMLWindowManager::SetIcon( const std::string &iconPath )
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

void SFMLWindowManager::SetTitle( const std::string &title )
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

U8 SFMLWindowManager::GetNewID()
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

bool SFMLWindowManager::CheckIsValid( U8 windowID ) const
{
    return mWindows.find( windowID ) != mWindows.end();
}

void SFMLWindowManager::OnWindowClose( const OnWindowCloseEvent &e )
{
    GetManagers()->application->Quit();
}