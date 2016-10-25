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

#include "mainloop.h"

#include "api/event.h"
#include "api/controller.h"

#include "common/program.h"

#include "math/scalar/vec2i.h"

#include "window/impl/sfmlWindowManager.h"

#include "gfx/bgfx/bgfxManager.h"

// TEMP
#include <bgfx/bgfx.h>
#include <bgfx/bgfxplatform.h>
// END TEMP

#include <iostream>

using namespace EDK::Graphics;

void EDK::RegisterControllers()
{
    Controller::Add<EDK::SFMLWindowManager>();
    Controller::Add<EDK::Graphics::BgfxManager>();
}

void EDK::MainLoop( S32 argc, char **argv )
{
    Program gameInstance( argc, argv );

    RegisterControllers();

    gameInstance.Init();

    //
    // TEMP section
    //

    EDK::SFMLWindowManager *windowManager = Controller::Get<EDK::SFMLWindowManager>();

    U8 windowID = windowManager->CreateNewWindow( Vec2I( 800, 600 ), Window::Style::Closable );

    uint32_t m_width = 800;
    uint32_t m_height = 600;
    uint32_t m_debug = BGFX_DEBUG_TEXT;
    uint32_t m_reset  = BGFX_RESET_VSYNC;

    EDK::VideoSwitchEvent videoEvent;
    videoEvent.interface = EDK::Graphics::Interface::Direct3D11;
    videoEvent.mainwindow.hwnd = windowManager->GetHandle( windowID );
    videoEvent.mainwindow.format = DataFormat::Format_RGBA_8_U;
    videoEvent.mainwindow.swapChainFlags = 0;
    videoEvent.mainwindow.size = Vec2I( 800, 600 );

    Event::Post( videoEvent );

    bool init_bgfx = true;
    // TEMP

    while ( gameInstance.IsRunning() )
    {
        gameInstance.Update();

        if ( init_bgfx )
        {
            // Enable debug text.
            bgfx::setDebug( m_debug );

            // Set view 0 clear state.
            bgfx::setViewClear(
                0
                , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
                , 0x303030ff
                , 1.0f
                , 0
            );

            init_bgfx = false;
        }

        // TEMP
        // Set view 0 default viewport.
        bgfx::setViewRect( 0, 0, 0, uint16_t( m_width ), uint16_t( m_height ) );

        // This dummy draw call is here to make sure that view 0 is cleared
        // if no other draw calls are submitted to view 0.
        bgfx::touch( 0 );

        // Use debug font to print information about this example.
        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf( 0, 1, 0x4f, "bgfx/examples/00-helloworld" );
        bgfx::dbgTextPrintf( 0, 2, 0x6f, "Description: Initialization and debug text." );

        // END TEMP

        Controller::Get<EDK::Graphics::BgfxManager>()->GetMainWindow()->Present();
    }
}