#include "gfx/abstract/gfxRenderTarget.h"

EDK::Graphics::RenderTarget::RenderTarget()
{
}

EDK::Graphics::ViewPort::ViewPort() :
    x( 0 ), y( 0 ), width( 0 ), height( 0 )
{

}

EDK::Graphics::ViewPort::ViewPort( U32 x, U32 y, U32 w, U32 h ) :
    x( x ), y( y ), width( w ), height( h )
{

}

EDK::Graphics::Scissor::Scissor() :
    x( 0 ), y( 0 ), width( 0 ), height( 0 )
{

}

EDK::Graphics::Scissor::Scissor( U32 x, U32 y, U32 w, U32 h ) :
    x( x ), y( y ), width( w ), height( h )
{

}

EDK::Graphics::ClearStrategy::ClearStrategy() :
    flags( ClearColour | ClearDepth | ClearStencil ), colour( 0x000000ff ), depth( 1.0 ), stencil( 0 )
{

}

EDK::Graphics::ClearStrategy::ClearStrategy( U32 flags, U32 colour, F32 depth, U8 stencil ) :
    flags( flags ), colour( colour ), depth( depth ), stencil( stencil )
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

EDK::Graphics::FrameBuffer::~FrameBuffer()
{

}