#include "gfx/bgfx/bgfxPipelineState.h"

EDK::Graphics::BgfxGraphicsPipelineState::BgfxGraphicsPipelineState() :
    mShader( nullptr ), mBgfxStateFlags( 0 ), mBgfxFrontStencilFlags( 0 ),
    mBgfxBackStencilFlags( 0 )
{

}

EDK::Graphics::GraphicsPipelineStateDesc EDK::Graphics::BgfxGraphicsPipelineState::QueryDesc() const
{
    return mDesc;
}

const EDK::Graphics::GraphicsShaderProgram *EDK::Graphics::BgfxGraphicsPipelineState::GetShaderProgram() const
{
    return mShader;
}

U64 EDK::Graphics::BgfxGraphicsPipelineState::GetBgfxStateFlags() const
{
    return mBgfxStateFlags;
}

U32 EDK::Graphics::BgfxGraphicsPipelineState::GetBgfxFrontStencilFlags() const
{
    return mBgfxFrontStencilFlags;   
}

U32 EDK::Graphics::BgfxGraphicsPipelineState::GetBgfxBackStencilFlags() const
{
    return mBgfxBackStencilFlags;
}

void EDK::Graphics::BgfxGraphicsPipelineState::OnInit()
{

}

void EDK::Graphics::BgfxGraphicsPipelineState::OnRelease()
{

}

void EDK::Graphics::BgfxGraphicsPipelineState::Init( const GraphicsPipelineStateDesc &desc,
                                                     const GraphicsShaderProgram *gsp, U64 stateflags, U32 fstencil, U32 bstencil )
{
    mDesc = desc;
    mShader = gsp;
    mBgfxStateFlags = stateflags;
    mBgfxFrontStencilFlags = fstencil;
    mBgfxBackStencilFlags = bstencil;
}