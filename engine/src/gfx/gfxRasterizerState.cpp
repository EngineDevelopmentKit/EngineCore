#include "gfx/gfxRasterizerState.h"

EDK::Graphics::RasterizerState::RasterizerState() :
    fillMode( FillMode::FillSolid ), cullMode( CullMode::CullBack ),
    faceMode( TriangleFaceMode::FrontByClockWise ), inputLayout( InputPrimitives::TriangleList ),
    msaaSamples( 0 ), lineAntiAliasing( false )
{

}