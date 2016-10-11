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
#include "common/types.h"

#include "math/scalar/vec2i.h"

#include "window/impl/sfmlWindow.h"

#include <string>

EDK::SFMLWindow::SFMLWindow()
{
    
}

EDK::SFMLWindow::~SFMLWindow() 
{
    
}

void EDK::SFMLWindow::Close()
{
    mWindowImpl.close();
}

void EDK::SFMLWindow::Open( const Vec2I &size, const std::string &title, Window::Style style ) 
{
    mWindowImpl.create( sf::VideoMode( size[0], size[1] ), title, EngineEnumToSfmlEnum( style ) );
}

bool EDK::SFMLWindow::IsOpen() const 
{ 
    return mWindowImpl.isOpen();
}

Vec2I EDK::SFMLWindow::GetSize() const
{ 
    sf::Vector2u size = mWindowImpl.getSize();
    
    return Vec2I( (S32)size.x, (S32)size.y );
}

Vec2I EDK::SFMLWindow::GetPosition() const 
{ 
    sf::Vector2i pos = mWindowImpl.getPosition();
    
    return Vec2I( (S32)pos.x, (S32)pos.y );
}

void EDK::SFMLWindow::SetSize( const Vec2I &v ) 
{
    mWindowImpl.setSize( sf::Vector2u( v[0], v[1] ) );
}

void EDK::SFMLWindow::SetPosition( const Vec2I &v ) 
{
    mWindowImpl.setPosition( sf::Vector2i( v[0], v[1] ) );
}

void EDK::SFMLWindow::SetVisible( bool mode ) 
{
    mWindowImpl.setVisible( mode );
}

void EDK::SFMLWindow::SetCursorVisible( bool mode ) 
{
    mWindowImpl.setMouseCursorVisible( mode );
}

void EDK::SFMLWindow::SetFullScreenMode( bool mode ) 
{
    
}

void EDK::SFMLWindow::SetBorderlessMode( bool mode ) 
{
    
}
        
void EDK::SFMLWindow::SetIcon( const std::string &path ) 
{
    
}

void EDK::SFMLWindow::SetTitle( const std::string &title ) 
{
    
}
        
void EDK::SFMLWindow::Release()
{
    
}
void EDK::SFMLWindow::ProcessEvents() 
{
    // Event processing
   sf::Event event;
   while (mWindowImpl.pollEvent(event))
   {
       // Request for closing the window
       if (event.type == sf::Event::Closed)
           Close();
   }
}

EDK::NativeWindowHandle EDK::SFMLWindow::GetNativeWindowHandle() const 
{ 

}

void EDK::SFMLWindow::OnShow() 
{
    
}

void EDK::SFMLWindow::OnHide() 
{
    
}

void EDK::SFMLWindow::OnClose() 
{
    
}

void EDK::SFMLWindow::OnResize()
{
    
}

void EDK::SFMLWindow::OnReposition() 
{
    
}

U32 EDK::SFMLWindow::EngineEnumToSfmlEnum( Window::Style style ) const
{
    switch ( style )
    {
        case Window::Style::Plain:
        
            return sf::Style::None;
            
        case Window::Style::CaptionBar:
        
            return sf::Style::Titlebar;
            
        case Window::Style::Resizable:
        
            return sf::Style::Resize;
            
        case Window::Style::Closable:
        
            return sf::Style::Close;
            
        case Window::Style::Fullscreen:
        
            return sf::Style::Fullscreen;
            
        default:
        
            return sf::Style::Default;
    } 
}