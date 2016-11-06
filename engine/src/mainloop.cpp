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

#include "common/file.h"
#include "common/program.h"
#include "common/deltaTime.h"

#include "math/scalar/vec2i.h"

#include "window/impl/sfmlWindowManager.h"

#include "gfx/bgfx/bgfxManager.h"
#include "gfx/bgfx/bgfxIndexBuffer.h"
#include "gfx/bgfx/bgfxVertexBuffer.h"
#include "gfx/bgfx/bgfxCommandList.h"
#include "gfx/bgfx/bgfxShaderBlob.h"
#include "gfx/bgfx/bgfxShaderProgram.h"

// TEMP
#include <bx/bx.h>
#include <bx/fpumath.h>
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

void EDK::MainLoop( S32 argc, char **argv )
{
    Program gameInstance( argc, argv );

    RegisterControllers();

    gameInstance.Init();

    //
    // TEMP section
    //

    EDK::SFMLWindowManager *windowManager = Controller::Get<EDK::SFMLWindowManager>();
    EDK::Graphics::BgfxManager *gfxManager = Controller::Get<EDK::Graphics::BgfxManager>();

    U32 width = 800;
    U32 height = 600;
    U32 debug = BGFX_DEBUG_TEXT;

    U8 windowID = windowManager->CreateNewWindow( Vec2I( width, height ), Window::Style::Closable );

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
    const PipelineState *pipelineSate = nullptr;
    const PixelShaderBlob *psblob = nullptr;
    const VertexShaderBlob *vsblob = nullptr;
    const GraphicsShaderProgram *shaderProgram = nullptr;
    GraphicsCommandList *commandList = nullptr;

    std::vector<char> vs_buffer;
    std::vector<char> fs_buffer;
    
    while ( gameInstance.IsRunning() )
    {
        gameInstance.Update();

        if ( initBgfx )
        {
            // Enable debug text.
            bgfx::setDebug( debug );

            // Set view 0 clear state.
            bgfx::setViewClear( 0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0 );

            PipelineStateDesc pipelineStateDesc;
            pipelineSate = gfxManager->CreatePipelineState( pipelineStateDesc );

            BufferLayoutDecl vertexLayout;
            vertexLayout.Add( ShaderAttribute::Position, GpuDataFormat( RGBAView( 3, AttributeType::FLOAT_32 ) ) );
            vertexLayout.Add( ShaderAttribute::Color0, GpuDataFormat( RGBAView( 4, AttributeType::UINT_NORM_8 ) ) );

            vertexBuffer = gfxManager->CreateVertexBuffer( VertexBufferDesc( vertexLayout ), s_cubeVertices,
                                                           sizeof( PosColorVertex ) * 8 );

            indexBuffer = gfxManager->CreateIndexBuffer( IndexBufferDesc( AttributeType::UINT_16 ), s_cubeIndices,
                                                         sizeof( uint16_t ) * 36 );

            commandList = gfxManager->CreateGraphicsCommandList();

            std::ifstream vs_stream, fs_stream;
            File::ReadOpen( vs_stream, "vs_cubes.bin", Path::Type::Program, std::ios::binary | std::ios::ate );
            File::ReadOpen( fs_stream, "fs_cubes.bin", Path::Type::Program, std::ios::binary | std::ios::ate );

            if ( vs_stream.is_open() )
            {
                std::streamsize size = vs_stream.tellg();
                vs_stream.seekg( 0, std::ios::beg );
                vs_buffer.resize( size );

                if ( vs_stream.read( vs_buffer.data(), size ) )
                {
                    vsblob = gfxManager->CreateVertexShaderBlob( vs_buffer.data(), size );
                }

                vs_stream.close();
            }

            if ( fs_stream.is_open() )
            {
                std::streamsize size = fs_stream.tellg();
                fs_stream.seekg( 0, std::ios::beg );

                fs_buffer.resize( size );

                if ( fs_stream.read( fs_buffer.data(), size ) )
                {
                    psblob = gfxManager->CreateVertexShaderBlob( fs_buffer.data(), size );
                }

                fs_stream.close();
            }

            shaderProgram = gfxManager->CreateShaderProgram( vsblob, psblob );

            initBgfx = false;
        }


        // TEMP
        // Set view 0 default viewport.
        bgfx::setViewRect( 0, 0, 0, uint16_t( width ), uint16_t( height ) );

        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf( 0, 1, 0x4f, "bgfx/examples/01-cube" );
        bgfx::dbgTextPrintf( 0, 2, 0x6f, "Description: Rendering simple static mesh." );
        bgfx::dbgTextPrintf( 0, 3, 0x0f, String::Place( "Fps: {:.0f}", 1 / time.GetEasedDeltaTime() ).c_str() );
        bgfx::dbgTextPrintf( 0, 4, 0x0f, String::Place( "Mspf: {:f}", time.GetEasedDeltaTime() ).c_str() );

        float at[3] = { 0.0f, 0.0f,   0.0f };
        float eye[3] = { 0.0f, 0.0f, -35.0f };

        float view[16];
        bx::mtxLookAt( view, eye, at );

        float proj[16];
        bx::mtxProj( proj, 60.0f, float( width ) / float( height ), 0.1f, 100.0f );
        bgfx::setViewTransform( 0, view, proj );

        // Set view 0 default viewport.
        bgfx::setViewRect( 0, 0, 0, uint16_t( width ), uint16_t( height ) );

        // This dummy draw call is here to make sure that view 0 is cleared
        // if no other draw calls are submitted to view 0.
        bgfx::touch( 0 );

        // Submit 11x11 cubes.
        for ( uint32_t yy = 0; yy < 11; ++yy )
        {
            for ( uint32_t xx = 0; xx < 11; ++xx )
            {
                float mtx[16];
                bx::mtxRotateXY( mtx, xx * 0.21f, yy * 0.37f );
                mtx[12] = -15.0f + float( xx ) * 3.0f;
                mtx[13] = -15.0f + float( yy ) * 3.0f;
                mtx[14] = 0.0f;
                
                // Set model matrix for rendering.
                bgfx::setTransform( mtx );

                // Set vertex and index buffer.
                commandList->SetVertexBuffer( vertexBuffer );
                commandList->SetIndexBuffer( indexBuffer );

                // Set render states.
                bgfx::setState( BGFX_STATE_DEFAULT );

                // Submit primitive for rendering to view 0.
                if ( shaderProgram )
                {
                    bgfx::submit( 0, static_cast< const BgfxShaderProgram *>( shaderProgram )->GetProgramHandle() );
                }
            }
        }
        
        time.Update();
    }
}