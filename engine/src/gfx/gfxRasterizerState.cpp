#include "gfx/gfxRasterizerState.h"

EDK::Graphics::RasterizerState::RasterizerState() :
    fillMode( FillMode::FillSolid ), cullMode( CullMode::CullBack ),
    faceMode( TriangleFaceMode::FrontByCounterClockWise ), inputLayout( InputPrimitives::TriangleList ),
    msaaSamples( 0 ), lineAntiAliasing( false )
{

}