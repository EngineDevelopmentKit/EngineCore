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

#include "common/program.h"

//#include "ui.h"

#include <iostream>
#include <SFML/Window.hpp>

/*
int onClosing( uiWindow *w, void *windowAlive )
{
    *static_cast<bool *>( windowAlive ) = false;
    uiQuit();
    return 1;
}
*/

void EDK::MainLoop( S32 argc, char **argv )
{
    /*
    uiInitOptions o;
    uiWindow *w;

    memset( &o, 0, sizeof( uiInitOptions ) );
    uiInit( &o );

    bool windowActive = true;

    w = uiNewWindow( "Hello", 320, 240, 0 );
    uiWindowSetMargined( w, 1 );
    uiWindowOnClosing( w, onClosing,  &windowActive );

    uiControlShow( uiControl( w ) );
    uiControlEnabledToUser( uiControl( w ) );
    uiMainSteps();
    */

    sf::Window window( sf::VideoMode( 800, 600 ), "SFML window" );

    Program gameInstance( argc, argv );

    gameInstance.Init();

    //while ( gameInstance.IsRunning() && windowActive )
    while ( gameInstance.IsRunning() )
    {
        // Event processing
        sf::Event event;

        while ( window.pollEvent( event ) )
        {
            // Request for closing the window
            if ( event.type == sf::Event::Closed )
            {
                window.close();
            }
        }

        gameInstance.Update();

        //uiMainStep( 0 );
    }
}