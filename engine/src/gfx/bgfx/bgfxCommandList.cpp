#include "gfx/bgfx/bgfxCommandList.h"
#include "gfx/bgfx/bgfxIndexBuffer.h"
#include "gfx/bgfx/bgfxVertexBuffer.h"
#include "gfx/bgfx/bgfxPipelineState.h"
#include "gfx/bgfx/bgfxShaderProgram.h"
#include "gfx/bgfx/bgfxEnumTranslate.h"

#include "common/util.h"

EDK::Graphics::BgfxGraphicsCommandList::BgfxGraphicsCommandList() :
    mDrawCalls( 0 ), mActiveProgram( nullptr )
{

}

void EDK::Graphics::BgfxGraphicsCommandList::OnInit()
{

}

void EDK::Graphics::BgfxGraphicsCommandList::OnRelease()
{

}

void EDK::Graphics::BgfxGraphicsCommandList::BeginRecording()
{
    // Clear state
    mDrawCalls = 0;
    mActiveProgram = nullptr;

    bgfx::touch( 0 );
}

void EDK::Graphics::BgfxGraphicsCommandList::EndRecording()
{

}

void EDK::Graphics::BgfxGraphicsCommandList::SetVertexBuffer( const VertexBuffer *vb )
{
    bgfx::setVertexBuffer( static_cast<const BgfxVertexBuffer *>( vb )->GetVertexBufferHandle() );
}

void EDK::Graphics::BgfxGraphicsCommandList::SetVertexBufferRange( const VertexBuffer *vb, U32 start, U32 num )
{
    bgfx::setVertexBuffer( static_cast<const BgfxVertexBuffer *>( vb )->GetVertexBufferHandle(), start, num );
}

void EDK::Graphics::BgfxGraphicsCommandList::SetIndexBuffer( const IndexBuffer *ib )
{
    bgfx::setIndexBuffer( static_cast<const BgfxIndexBuffer *>( ib )->GetIndexBufferHandle() );
}

void EDK::Graphics::BgfxGraphicsCommandList::SetIndexBufferRange( const IndexBuffer *ib, U32 start, U32 num )
{
    bgfx::setIndexBuffer( static_cast<const BgfxIndexBuffer *>( ib )->GetIndexBufferHandle(), start, num );
}

void EDK::Graphics::BgfxGraphicsCommandList::SetPipelineState( const GraphicsPipelineState *pso )
{
    const BgfxGraphicsPipelineState *bpso = static_cast<const BgfxGraphicsPipelineState *>( pso );

    // set the active shader
    mActiveProgram = bpso->GetShaderProgram();

    const GraphicsPipelineStateDesc &desc = bpso->QueryDesc();

    U64 bgfxStateFlags = 0;

    bgfxStateFlags |= GetBgfxDepthTest( desc.depthStencilState.depthTestOp );

    if ( desc.depthStencilState.enableDepthWrite )
    {
        bgfxStateFlags |= BGFX_STATE_DEPTH_WRITE;
    }

    if ( desc.rasterizerState.fillMode == FillMode::FillWireFrame )
    {
        bgfx::setDebug( BGFX_DEBUG_WIREFRAME | BGFX_DEBUG_TEXT );
    }

    bgfxStateFlags |= GetBgfxCullMode( desc.rasterizerState.cullMode, desc.rasterizerState.faceMode );
    bgfxStateFlags |= GetBgfxPrimitiveFlags( desc.rasterizerState.inputLayout );

    if ( desc.rasterizerState.msaaSamples > 0 )
    {
        bgfxStateFlags |= BGFX_STATE_MSAA;
    }

    if ( desc.rasterizerState.lineAntiAliasing )
    {
        bgfxStateFlags |= BGFX_STATE_LINEAA;
    }

    // TEMP do write RGBA
    if ( desc.renderTargetState.writeMask == ChannelTarget::ChannelA )
    {
        bgfxStateFlags |= BGFX_STATE_ALPHA_WRITE;
    }
    else if ( desc.renderTargetState.writeMask == ChannelTarget::ChannelRGB )
    {
        bgfxStateFlags |= BGFX_STATE_RGB_WRITE;
    }
    else if ( desc.renderTargetState.writeMask == ChannelTarget::ChannelRGBA )
    {
        bgfxStateFlags |= BGFX_STATE_RGB_WRITE | BGFX_STATE_ALPHA_WRITE;
    }

    if ( IS_SET( desc.renderTargetState.blendStateFlags, BlendStateFlags::EnableAlphaToCoverage ) )
    {
        bgfxStateFlags |= BGFX_STATE_BLEND_ALPHA_TO_COVERAGE;
    }

    bgfxStateFlags |= BGFX_STATE_BLEND_FUNC_SEPARATE( GetBgfxBlendSource( desc.renderTargetState.srcBlendValue ),
                                                      GetBgfxBlendSource( desc.renderTargetState.destBlendValue ),
                                                      GetBgfxBlendSource( desc.renderTargetState.srcBlendAlpha ),
                                                      GetBgfxBlendSource( desc.renderTargetState.destBlendAlpha ) );

    bgfxStateFlags |= BGFX_STATE_BLEND_EQUATION_SEPARATE( GetBgfxBlendFunc( desc.renderTargetState.blendOp ),
                                                          GetBgfxBlendFunc( desc.renderTargetState.alphaBlendOp ) );

    bgfx::setState( bgfxStateFlags );

    if ( desc.depthStencilState.enableStencilTest )
    {
        U32 frontFaceStencil = GetBgfxStencilFlags( desc.depthStencilState.frontFaceStencilTest );
        U32 backFaceStencil = GetBgfxStencilFlags( desc.depthStencilState.backFaceStencilTest );

        bgfx::setStencil( frontFaceStencil, backFaceStencil );
    }
}

void EDK::Graphics::BgfxGraphicsCommandList::Submit( U32 sortKey )
{
    mDrawCalls += bgfx::submit( 0, static_cast<const BgfxShaderProgram *>( mActiveProgram )->GetProgramHandle(),
                                sortKey, true );
}


