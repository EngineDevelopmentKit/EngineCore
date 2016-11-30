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

#include "ecs.h"

#include "common/program.h"

#include "gfx/gfx.h"

#include "api/event.h"
#include "api/plugin.h"
#include "api/controller.h"

#include "common/file.h"
#include "common/program.h"
#include "common/deltaTime.h"

#include "math/scalar/vec3.h"
#include "math/scalar/vec2i.h"
#include "math/scalar/matrix4.h"

#include "window/window.h"
#include "window/sfmlWindowManager.h"
#include "window/abstract/windowStyle.h"

#include "gfx/bgfx/bgfxManager.h"
#include "gfx/bgfx/bgfxIndexBuffer.h"
#include "gfx/bgfx/bgfxVertexBuffer.h"
#include "gfx/bgfx/bgfxCommandList.h"
#include "gfx/bgfx/bgfxShaderBlob.h"
#include "gfx/bgfx/bgfxShaderProgram.h"

// TEMP
//#include <bx/bx.h>
//#include <bx/fpumath.h>
//#include <bgfx/bgfx.h>
//#include <bgfx/bgfxplatform.h>
// END TEMP

#include <iostream>
#include <stdlib.h>

using namespace EDK::Graphics;

struct PosColorVertex
{
    float m_x;
    float m_y;
    float m_z;
    uint32_t m_abgr;
};

static PosColorVertex s_cubeVertices[8] =
{
    { -1.0f,  1.0f,  1.0f, 0xff000000 },
    { 1.0f,  1.0f,  1.0f, 0xff0000ff },
    { -1.0f, -1.0f,  1.0f, 0xff00ff00 },
    { 1.0f, -1.0f,  1.0f, 0xff00ffff },
    { -1.0f,  1.0f, -1.0f, 0xffff0000 },
    { 1.0f,  1.0f, -1.0f, 0xffff00ff },
    { -1.0f, -1.0f, -1.0f, 0xffffff00 },
    { 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static uint16_t s_cubeIndices[36] =
{
    0, 1, 2, // 0
    1, 3, 2,
    4, 6, 5, // 2
    5, 6, 7,
    0, 2, 4, // 4
    4, 2, 6,
    1, 5, 3, // 6
    5, 7, 3,
    0, 4, 1, // 8
    4, 5, 1,
    2, 3, 6, // 10
    6, 3, 7,
};

std::vector<char> ReadBinShader( const std::string &location )
{
    EDK::Graphics::BgfxManager *gfxManager = Controller::Get<EDK::Graphics::BgfxManager>();

    std::ifstream s_stream;
    std::vector<char> s_buffer;

    File::ReadOpen( s_stream, location.c_str(), Path::Type::Program, std::ios::binary | std::ios::ate );

    const VertexShaderBlob *vsblob = nullptr;

    if ( s_stream.is_open() )
    {
        std::streamsize size = s_stream.tellg();
        s_stream.seekg( 0, std::ios::beg );
        s_buffer.resize( size );

        s_stream.read( s_buffer.data(), size );

        s_stream.close();
    }

    return s_buffer;
}


S32 main( S32 argc, char **argv )
{
    Program program( argc, argv );

    Plugin::Add< ECSPlugin >();
    Plugin::Add< WindowPlugin >();
    Plugin::Add< GraphicsPlugin >();

    program.Init();

    //
    // TEMP section
    //

    EDK::SFMLWindowManager *windowManager = Controller::Get<EDK::SFMLWindowManager>();
    EDK::Graphics::BgfxManager *gfxManager = Controller::Get<EDK::Graphics::BgfxManager>();

    U32 width = 800;
    U32 height = 600;
    U32 debug = BGFX_DEBUG_TEXT;

    U8 windowID = windowManager->CreateNewWindow( Vec2I( width, height ), EDK::Window::Style::Closable );

    EDK::VideoSwitchEvent videoEvent;
    videoEvent.interface = EDK::Graphics::Interface::Direct3D11;
    videoEvent.mainwindow.hwnd = windowManager->GetHandle( windowID );
    videoEvent.mainwindow.swapChainFlags = 0u;
    videoEvent.mainwindow.size = Vec2I( width, height );

    Event::Post( videoEvent );

    bool initBgfx = true;
    // TEMP

    DeltaTime time;

    const IndexBuffer *indexBuffer = nullptr;
    const VertexBuffer *vertexBuffer = nullptr;
    const GraphicsPipelineState *pipelineSate = nullptr;
    const PixelShaderBlob *psblob = nullptr;
    const VertexShaderBlob *vsblob = nullptr;
    const GraphicsShaderProgram *shaderProgram = nullptr;
    GraphicsCommandList *commandList = nullptr;

    std::vector<char> vs_buffer;
    std::vector<char> fs_buffer;

    while ( program.IsRunning() )
    {
        program.Update();

        if ( initBgfx )
        {
            // Enable debug text.
            bgfx::setDebug( debug );

            BufferLayoutDecl vertexLayout;
            vertexLayout.Add( ShaderAttribute::Position, GpuDataFormat( RGBAView( 3, AttributeType::FLOAT_32 ) ) );
            vertexLayout.Add( ShaderAttribute::Color0, GpuDataFormat( RGBAView( 4, AttributeType::UINT_NORM_8 ) ) );

            vertexBuffer = gfxManager->CreateVertexBuffer( VertexBufferDesc( vertexLayout ), s_cubeVertices,
                                                           sizeof( PosColorVertex ) * 8 );

            indexBuffer = gfxManager->CreateIndexBuffer( IndexBufferDesc( AttributeType::UINT_16 ), s_cubeIndices,
                                                         sizeof( uint16_t ) * 36 );

            commandList = gfxManager->CreateGraphicsCommandList();

            vs_buffer = ReadBinShader( "vs_cubes.bin" );
            fs_buffer = ReadBinShader( "fs_cubes.bin" );
            vsblob = gfxManager->CreateVertexShaderBlob( vs_buffer.data(), vs_buffer.size() );
            psblob = gfxManager->CreateVertexShaderBlob( fs_buffer.data(), fs_buffer.size() );

            shaderProgram = gfxManager->CreateShaderProgram( vsblob, psblob );

            GraphicsPipelineStateDesc pipelineStateDesc;
            //pipelineStateDesc.rasterizerState.fillMode = FillMode::FillWireFrame;
            pipelineSate = gfxManager->CreatePipelineState( pipelineStateDesc, shaderProgram );

            initBgfx = false;
        }

        Vec3f at = { 0.0f, 0.0f, 0.0f };
        Vec3f eye = { 0.0f, 0.0f, -35.0f };
        Matrix4f view = gfxManager->LookAtMatrix( eye, at );
        Matrix4f proj = gfxManager->ProjMatrix( 60.0f, width, height, 0.1f, 100.0f );

        // Setup the command list for recording
        commandList->BeginRecording( nullptr, ViewPort( 0, 0, width, height ),
                                     ClearStrategy( ClearChannel::ClearColour | ClearChannel::ClearDepth, 0x303030ff, 1.0f, 0 ),
                                     view, proj, Scissor() );

        //bgfx::dbgTextClear();
        //bgfx::dbgTextPrintf( 0, 0, 0x4f, "bgfx/examples/01-cube" );
        //bgfx::dbgTextPrintf( 0, 1, 0x6f, "Description: Rendering simple static mesh." );
        //bgfx::dbgTextPrintf( 0, 2, 0x0f, String::Place( "Fps: {:.0f}", 1 / time.GetEasedDeltaTime() ).c_str() );
        //bgfx::dbgTextPrintf( 0, 3, 0x0f, String::Place( "Mspf: {:f}", time.GetEasedDeltaTime() ).c_str() );


        // Set vertex and index buffer.
        commandList->SetVertexBuffer( vertexBuffer );
        commandList->SetIndexBuffer( indexBuffer );
        commandList->SetPipelineState( pipelineSate );


        // Submit 11x11 cubes.
        for ( U32 yy = 0; yy < 11; ++yy )
        {
            for ( U32 xx = 0; xx < 11; ++xx )
            {
                Matrix4f mtxf;
                mtxf.SetIdentity();
                mtxf[3][0] = -15.0f + float( xx ) * 3.0f;
                mtxf[3][1] = -15.0f + float( yy ) * 3.0f;
                mtxf[3][2] = 0.0f;

                // Submit primitive for rendering to view 0.
                if ( shaderProgram )
                {
                    commandList->Submit( &mtxf );
                }
            }
        }

        commandList->EndRecording();

        time.Update();
    }

    return 0;
}
