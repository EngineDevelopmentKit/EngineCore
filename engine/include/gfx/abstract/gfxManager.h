#pragma once
#ifndef __EDK_GFX_FACTORY_H__
#define __EDK_GFX_FACTORY_H__

#include "events/abstract/IEvent.h"

#include "gfx/gfxArchitecture.h"
#include "gfx/abstract/gfxSwapChain.h"
#include "gfx/abstract/gfxShaderBlob.h"
#include "gfx/abstract/gfxIndexBuffer.h"
#include "gfx/abstract/gfxCommandList.h"
#include "gfx/abstract/gfxVertexBuffer.h"
#include "gfx/abstract/gfxPipelineState.h"
#include "gfx/abstract/gfxShaderProgram.h"

#include "manager/abstract/abstractManager.h"

#include "math/scalar/matrix4.h"

namespace EDK
{
    struct VideoSwitchEvent : public IEvent
    {
        Graphics::VideoCard videocard;
        Graphics::Interface interface;
        Graphics::SwapChainDesc mainwindow;
    };

    namespace Graphics
    {
        class Manager : public AbstractManager
        {
        public:

            virtual ~Manager() {}

            virtual Matrix4f LookAtMatrix( const Vec3f &eye, const Vec3f &at ) const  = 0;
            virtual Matrix4f ProjMatrix( F32 fov, U32 width, U32 height, F32 near, F32 far ) const = 0;

            virtual const IndexBuffer *CreateIndexBuffer( const IndexBufferDesc &desc, void *memory, size_t memSize ) = 0;
            virtual const VertexBuffer *CreateVertexBuffer( const VertexBufferDesc &desc, void *memory, size_t memSize ) = 0;
            virtual const GraphicsPipelineState *CreatePipelineState( const GraphicsPipelineStateDesc &desc,
                                                                      const GraphicsShaderProgram *gsp ) = 0;
            virtual const PixelShaderBlob *CreatePixelShaderBlob( void *memory, size_t memSize ) = 0;
            virtual const VertexShaderBlob *CreateVertexShaderBlob( void *memory, size_t memSize ) = 0;
            virtual const GraphicsShaderProgram *CreateShaderProgram( const VertexShaderBlob *vs, const PixelShaderBlob *ps ) = 0;

            virtual GraphicsCommandList *CreateGraphicsCommandList() = 0;

            virtual const SwapChain *GetMainWindow() = 0;
        };
    }
}

#endif