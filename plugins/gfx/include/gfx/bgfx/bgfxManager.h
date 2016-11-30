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
#ifndef __EDK_BGFX_GRAPHICSMANAGER_H__
#define __EDK_BGFX_GRAPHICSMANAGER_H__

#include "gfx/gfxBufferDecl.h"
#include "gfx/abstract/gfxManager.h"

#include <mutex>
#include <bgfx/bgfx.h>

/// @addtogroup Windows
/// @{

/**
* Manager for the graphics handles.
*
* @sa  Manager
*/

template< typename tBase >
class AbstractObjectPool;

namespace EDK
{
    namespace Graphics
    {
        class BgfxManager
            : public Graphics::Manager
        {
        public:

            BgfxManager();

            virtual void OnInit() override;
            virtual void OnPostInit() override;
            virtual void OnRelease() override;
            virtual void OnUpdate() override;

            virtual Matrix4f LookAtMatrix( const Vec3f &eye, const Vec3f &at ) const override;
            virtual Matrix4f ProjMatrix( F32 fov, U32 width, U32 height, F32 near, F32 far ) const override;

            virtual const IndexBuffer *CreateIndexBuffer( const IndexBufferDesc &desc, void *memory, size_t memSize ) override;
            virtual const VertexBuffer *CreateVertexBuffer( const VertexBufferDesc &desc, void *memory, size_t memSize ) override;
            virtual const GraphicsPipelineState *CreatePipelineState( const GraphicsPipelineStateDesc &desc,
                                                                      const GraphicsShaderProgram *gsp ) override;
            virtual const PixelShaderBlob *CreatePixelShaderBlob( void *memory, size_t memSize ) override;
            virtual const VertexShaderBlob *CreateVertexShaderBlob( void *memory, size_t memSize ) override;
            virtual const GraphicsShaderProgram *CreateShaderProgram( const VertexShaderBlob *vs,
                                                                      const PixelShaderBlob *ps ) override;

            virtual GraphicsCommandList *CreateGraphicsCommandList( const std::string &name = "Undefined" ) override;

            virtual const SwapChain *GetMainWindow() override;

            bool IsDirty() const;

        protected:

            void Reinitialize( const SwapChainDesc &desc, const VideoCard &card, const Interface interf );

            void OnVideoSwitch( const VideoSwitchEvent &e );

        private:

            SwapChain *mMainwindow;
            mutable std::mutex mMutex;
            bool mHasValidInterfaceLink;

            struct VideoState
            {
                VideoState();

                bool dirty;
                VideoCard card;
                Interface interf;
                SwapChainDesc desc;

            } mVideoState;

            AbstractObjectPool< SwapChain > *mSwapChainPool;
            AbstractObjectPool< ShaderBlob > *mShaderBlobPool;
            AbstractObjectPool< IndexBuffer > *mIndexBufferPool;
            AbstractObjectPool< VertexBuffer > *mVertexBufferPool;
            AbstractObjectPool< GraphicsPipelineState > *mPipelineStatePool;
            AbstractObjectPool< ShaderProgram > *mShaderProgramPool;
            AbstractObjectPool< GraphicsCommandList > *mGraphicsCommandListPool;
        };

    }
}

#endif

