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

#include "api/controller.h"

#include "common/program.h"

#include "math/scalar/vec2i.h"

#include "window/windowManager.h"

#include <iostream>

void EDK::RegisterControllers()
{
    SystemManager::Get()->GetManagers()->controller->Add<EDK::WindowManager>();
}

void EDK::MainLoop( S32 argc, char **argv )
{
    Program gameInstance( argc, argv );

    gameInstance.Init();

    RegisterControllers();
    
    //
    // TEMP section
    //
    
    EDK::WindowManager *windowManager = SystemManager::Get()->GetManagers()->controller->Get<EDK::WindowManager>();
    
    windowManager->CreateNewWindow( Vec2I( 800,600) );

    // TEMP

    while ( gameInstance.IsRunning() )
    {
        gameInstance.Update();
    }
}