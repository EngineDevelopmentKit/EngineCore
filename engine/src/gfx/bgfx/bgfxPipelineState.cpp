#include "gfx/bgfx/bgfxPipelineState.h"

EDK::Graphics::BgfxGraphicsPipelineState::BgfxGraphicsPipelineState() :
    mShader( nullptr )
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

void EDK::Graphics::BgfxGraphicsPipelineState::OnInit()
{

}

void EDK::Graphics::BgfxGraphicsPipelineState::OnRelease()
{

}

void EDK::Graphics::BgfxGraphicsPipelineState::Init( const GraphicsPipelineStateDesc &desc,
                                                     const GraphicsShaderProgram *gsp )
{
    mDesc = desc;
    mShader = gsp;
}