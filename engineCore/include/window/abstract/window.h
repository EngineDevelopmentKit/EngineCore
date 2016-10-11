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

#pragma once
#ifndef __EDK_WINDOW_H__
#define __EDK_WINDOW_H__

#include "common/types.h"

#include "math/scalar/vec2i.h"

#include "events/abstract/IEvent.h"

#include "window/windowStyle.h"
#include "window/abstract/windowHandle.h"

#include <string>

namespace EDK
{
    class OnWindowShowEvent : public IEvent
    {
            
    };
    
    class OnWindowHideEvent : public IEvent
    {
            
    };
    
    class OnWindowCloseEvent : public IEvent
    {
            
    };
    
    class OnWindowOpenEvent : public IEvent
    {
            
    };
    
    class OnWindowResizeEvent : public IEvent
    {
            
    };
    
    class OnWindowRepositionEvent : public IEvent
    {
            
    };
     
    class OnWindowHandleChangeEvent : public IEvent
    {
            
    };
    
    class IWindow
    {
    public:

        virtual ~IWindow() {}

        virtual void Close() = 0;
        virtual void Open( const Vec2I &size, const std::string &title, Window::Style style = Window::Style::Default ) = 0;

        virtual bool IsOpen() const = 0;

        virtual Vec2I GetSize() const = 0;
        virtual Vec2I GetPosition() const = 0;

        virtual void SetSize( const Vec2I &v ) = 0;
        virtual void SetPosition( const Vec2I &v ) = 0;
        virtual void SetStyle( Window::Style style ) = 0;
          
        virtual void SetVisible( bool mode ) = 0;
        virtual void SetCursorVisible( bool mode ) = 0;
        
        virtual void SetIcon( const std::string &path ) = 0;
        virtual void SetTitle( const std::string &title ) = 0;
        
        virtual void Release() = 0;
        virtual void ProcessEvents() = 0;

        virtual NativeWindowHandle GetNativeWindowHandle() const = 0;

    };
}

#endif