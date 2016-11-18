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
#ifndef __EDK_WINDOWMANAGER_H__
#define __EDK_WINDOWMANAGER_H__

#include "window/abstract/windowHandle.h"
#include "window/abstract/windowStyle.h"
#include "window/abstract/window.h"

#include "manager/abstract/abstractManager.h"

#include <mutex>

/// @addtogroup Windows
/// @{

/**
* Manager for the windows.
*
* @sa  Manager
*/

class Vec2I;

namespace EDK
{
    struct OnWindowCloseEvent;

    class WindowManager
        : public AbstractManager
    {
    public:

        WindowManager();

        /// @name Window
        /// @{

        /**
        * Creates a new window.
        *
        * @param   style   (Optional) the style.
        */

        virtual U8 CreateNewWindow( const Vec2I &size, Window::Style style = Window::Style::Default ) = 0;

        /**
        * Destroys the window described by the given ID.
        *
        * @param   windowID    Identifier for the window.
        */

        virtual void DestroyWindow( U8 windowID = 0 ) = 0;

        /**
        * Query if the given ID is valid.
        *
        * @param   windowID    Identifier for the window.
        *
        * @return  true if valid, false if not.
        */

        virtual bool IsValid( U8 windowID = 0 ) const = 0;

        /**
        * Gets the window handle.
        *
        * @param   windowID    (optional) identifier for the window.
        *
        * @return  The handle.
        */

        virtual NativeWindowHandle GetHandle( U8 windowID = 0 ) const = 0;

        /**
        * Sets the ID of the main window.
        *
        * @param   windowID    Identifier for the window.
        */

        virtual void SetMainWindow( U8 windowID ) = 0;

        /**
        * Gets the main window.
        *
        * @return  The main window.
        */

        virtual U8 GetMainWindow() const = 0;

        /**
        * Gets the window count.
        *
        * @return  The window count.
        */

        virtual U8 GetWindowCount() const = 0;

        /// @}

        /// @name Appearance
        /// @{

        /**
        * Sets a size on the given window.
        *
        * @param   windowID    Identifier for the window. Takes
        *                      the main window if equal to 0.
        * @param   size        The size.
        */

        virtual void SetSize( const Vec2I &size, U8 windowID = 0 ) = 0;

        /**
        * Gets the size from the given window.
        *
        * @param   windowID    Identifier for the window. Takes
        *                      the main window if equal to 0.
        *
        * @return  The size.
        */

        virtual Vec2I GetSize( U8 windowID = 0 ) = 0;

        //Vec2I GetClientSize( U8 windowID = 0 );

        /**
        * Sets a position on the given window.
        *
        * @param   windowID    Identifier for the window. Takes
        *                      the main window if equal to 0.
        * @param   position    The position.
        */

        virtual void SetPosition( const Vec2I &position, U8 windowID = 0 ) = 0;

        /**
        * Gets the position from the given window.
        *
        * @param   windowID    Identifier for the window. Takes
        *                      the main window if equal to 0.
        *
        * @return  The position.
        */

        virtual Vec2I GetPosition( U8 windowID = 0 ) = 0;

        /**
        * Sets the given window to full screen.
        *
        * @param   windowID    Identifier for the window. Takes
        *                      the main window if equal to 0.
        * @param   fullscreen  true to set fullscreen.
        */

        //void SetFullScreen( bool fullscreen, U8 windowID = 0 );

        /**
        * Sets the given window visible.
        *
        * @param   windowID    Identifier for the window. Takes
        *                      the main window if equal to 0.
        * @param   visible     true to show the window, false to hide.
        */

        virtual void SetVisible( bool visible, U8 windowID = 0 ) = 0;

        /**
        * Sets an icon on all windows by setting an icon path.
        *
        * @param   iconPath    Full pathname of the icon file.
        */

        virtual void SetIcon( const std::string &iconPath ) = 0;

        /**
        * Sets the title on all windows.
        *
        * @param   title   The title.
        */

        virtual void SetTitle( const std::string &title ) = 0;

        /**
        * Sets cursor visible on all windows.
        *
        * @param   visible true to show, false to hide.
        */

        virtual void SetCursorVisible( bool visible ) = 0;

        /// @}
    };

    /// @}
}

#endif // __WINDOWMANAGER_H__

