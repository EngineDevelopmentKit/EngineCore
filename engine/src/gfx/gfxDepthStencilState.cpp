#include "gfx/gfxDepthStencilState.h"

EDK::Graphics::StencilTest::StencilTest() :
    onStencilFail( StencilOperation::StencilOpZero ),
    onStencilPassDepthFail( StencilOperation::StencilOpZero ),
    onStencilDepthPass( StencilOperation::StencilOpZero ),
    stencilCompareOp( ComparisonOperation::OpNever )
{}

EDK::Graphics::DepthStencilState::DepthStencilState() :
    enableDepthTest( false ), enableStencilTest( false ), enableDepthWrite( false ),
    stencilWriteMask( 0 ), stencilReadMask( 0 ),
    depthBias( 0.0 ), depthBiasClamp( 0.0 ), slopeScaledDepthBias( 0.0 ),
    depthBufferFormat( GpuDataFormat( SpecialDataFormat::R24S8 ) ),
    depthTestOp( ComparisonOperation::OpLess )
{

}