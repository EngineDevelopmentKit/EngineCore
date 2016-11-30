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
        Vec3f at = { 0.0f, 0.0f, 0.0f };
        Vec3f eye = { 0.0f, 0.0f, -35.0f };
        Matrix4f view = gfxManager->LookAtMatrix( eye, at );
        Matrix4f proj = gfxManager->ProjMatrix( 60.0f, width, height, 0.1f, 100.0f );
        // Setup the command list for recording
        commandList->BeginRecording( nullptr, ViewPort( 0, 0, width, height ),
                                     ClearStrategy( ClearChannel::ClearColour | ClearChannel::ClearDepth, 0x303030ff, 1.0f, 0 ),
                                     view, proj, Scissor() );