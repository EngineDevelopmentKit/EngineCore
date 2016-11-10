#include "gfx/gfxRenderTarget.h"

EDK::Graphics::RenderTarget::RenderTarget()
{
}

EDK::Graphics::RenderTargetState::RenderTargetState() :
    blendStateFlags( 0 ),
    srcBlendValue( BlendSource::BlendSrcColour ), destBlendValue( BlendSource::BlendDestColour ),
    blendOp( BlendOperation::BlendOpAdd ),
    srcBlendAlpha( BlendSource::BlendSrcAlpha ), destBlendAlpha( BlendSource::BlendDestAlpha ),
    alphaBlendOp( BlendOperation::BlendOpAdd ), writeMask( ChannelTarget::ChannelRGBA )
{

}