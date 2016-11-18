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
#ifndef __EDK_SFML_WINDOW_H__
#define __EDK_SFML_WINDOW_H__

#include "window/abstract/windowHandle.h"

#include "window/abstract/window.h"

#include "math/scalar/vec2i.h"

#include "common/types.h"

#include <SFML/Window.hpp>

namespace EDK
{
    class SFMLWindow :
        public IWindow
    {
    public:

        SFMLWindow( U8 id );
        virtual ~SFMLWindow() ;


        virtual void Close() override;
        virtual void Open( const Vec2I &size, const std::string &title, Window::Style style ) override;

        virtual bool IsOpen() const override;

        virtual Vec2I GetSize() const override;
        virtual Vec2I GetPosition() const override;

        virtual void SetSize( const Vec2I &v ) override;
        virtual void SetPosition( const Vec2I &v ) override;
        virtual void SetStyle( Window::Style style ) override;

        virtual void SetVisible( bool mode ) override;
        virtual void SetCursorVisible( bool mode ) override;

        virtual void SetIcon( const std::string &path ) override;
        virtual void SetTitle( const std::string &title ) override;

        virtual void Release() override;
        virtual void ProcessEvents() override;

        virtual NativeWindowHandle GetNativeWindowHandle() const override;

    private:

        U32 EngineEnumToSfmlEnum( Window::Style style ) const;

        U8 mWindowID;
        std::string mTitle;
        sf::Window mWindowImpl;
    };
}

#endif