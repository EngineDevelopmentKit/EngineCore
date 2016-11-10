#include "gfx/bgfx/bgfxEnumTranslate.h"
#include "gfx/bgfx/bgfxPipelineState.h"

#include <bgfx/bgfx.h>

U32 EDK::Graphics::GetBgfxStencilFlags( const StencilTest &stencil )
{
    U32 flags = 0;

    switch ( stencil.stencilCompareOp )
    {
    case ComparisonOperation::OpNever:
        flags |= BGFX_STENCIL_TEST_NEVER;
        break;

    case ComparisonOperation::OpLess:
        flags |= BGFX_STENCIL_TEST_LESS;
        break;

    case ComparisonOperation::OpEqual:
        flags |= BGFX_STENCIL_TEST_EQUAL;
        break;

    case ComparisonOperation::OpLessEqual:
        flags |= BGFX_STENCIL_TEST_LEQUAL;
        break;

    case ComparisonOperation::OpGreater:
        flags |= BGFX_STENCIL_TEST_GREATER;
        break;

    case ComparisonOperation::OpNotEqual:
        flags |= BGFX_STENCIL_TEST_NOTEQUAL;
        break;

    case ComparisonOperation::OpGreaterEqual:
        flags |= BGFX_STENCIL_TEST_GEQUAL;
        break;

    case ComparisonOperation::OpAlways:
        flags |= BGFX_STENCIL_TEST_ALWAYS;
        break;
    }

    switch ( stencil.onStencilFail )
    {
    case StencilOperation::StencilOpKeep:
        flags |= BGFX_STENCIL_OP_FAIL_S_KEEP;
        break;

    case StencilOperation::StencilOpZero:
        flags |= BGFX_STENCIL_OP_FAIL_S_ZERO;
        break;

    case StencilOperation::StencilOpReplace:
        flags |= BGFX_STENCIL_OP_FAIL_S_REPLACE;
        break;

    case StencilOperation::StencilOpIncr:
        flags |= BGFX_STENCIL_OP_FAIL_S_INCR;
        break;

    case StencilOperation::StencilOpIncrSat:
        flags |= BGFX_STENCIL_OP_FAIL_S_INCRSAT;
        break;

    case StencilOperation::StencilOpDecr:
        flags |= BGFX_STENCIL_OP_FAIL_S_DECR;
        break;

    case StencilOperation::StencilOpDecrSat:
        flags |= BGFX_STENCIL_OP_FAIL_S_DECRSAT;
        break;

    case StencilOperation::StencilOpInvert:
        flags |= BGFX_STENCIL_OP_FAIL_S_INVERT;
        break;
    }

    switch ( stencil.onStencilPassDepthFail )
    {
    case StencilOperation::StencilOpKeep:
        flags |= BGFX_STENCIL_OP_FAIL_Z_KEEP;
        break;

    case StencilOperation::StencilOpZero:
        flags |= BGFX_STENCIL_OP_FAIL_Z_ZERO;
        break;

    case StencilOperation::StencilOpReplace:
        flags |= BGFX_STENCIL_OP_FAIL_Z_REPLACE;
        break;

    case StencilOperation::StencilOpIncr:
        flags |= BGFX_STENCIL_OP_FAIL_Z_INCR;
        break;

    case StencilOperation::StencilOpIncrSat:
        flags |= BGFX_STENCIL_OP_FAIL_Z_INCRSAT;
        break;

    case StencilOperation::StencilOpDecr:
        flags |= BGFX_STENCIL_OP_FAIL_Z_DECR;
        break;

    case StencilOperation::StencilOpDecrSat:
        flags |= BGFX_STENCIL_OP_FAIL_Z_DECRSAT;
        break;

    case StencilOperation::StencilOpInvert:
        flags |= BGFX_STENCIL_OP_FAIL_Z_INVERT;
        break;
    }

    switch ( stencil.onStencilDepthPass )
    {
    case StencilOperation::StencilOpKeep:
        flags |= BGFX_STENCIL_OP_PASS_Z_KEEP;
        break;

    case StencilOperation::StencilOpZero:
        flags |= BGFX_STENCIL_OP_PASS_Z_ZERO;
        break;

    case StencilOperation::StencilOpReplace:
        flags |= BGFX_STENCIL_OP_PASS_Z_REPLACE;
        break;

    case StencilOperation::StencilOpIncr:
        flags |= BGFX_STENCIL_OP_PASS_Z_INCR;
        break;

    case StencilOperation::StencilOpIncrSat:
        flags |= BGFX_STENCIL_OP_PASS_Z_INCRSAT;
        break;

    case StencilOperation::StencilOpDecr:
        flags |= BGFX_STENCIL_OP_PASS_Z_DECR;
        break;

    case StencilOperation::StencilOpDecrSat:
        flags |= BGFX_STENCIL_OP_PASS_Z_DECRSAT;
        break;

    case StencilOperation::StencilOpInvert:
        flags |= BGFX_STENCIL_OP_PASS_Z_INVERT;
        break;
    }

    return flags;
}

U64 EDK::Graphics::GetBgfxDepthTest( ComparisonOperation op )
{
    U64 flags = 0;

    switch ( op )
    {
    case ComparisonOperation::OpNever:
        flags |= BGFX_STATE_DEPTH_TEST_NEVER;
        break;

    case ComparisonOperation::OpLess:
        flags |= BGFX_STATE_DEPTH_TEST_LESS;
        break;

    case ComparisonOperation::OpEqual:
        flags |= BGFX_STATE_DEPTH_TEST_EQUAL;
        break;

    case ComparisonOperation::OpLessEqual:
        flags |= BGFX_STATE_DEPTH_TEST_LEQUAL;
        break;

    case ComparisonOperation::OpGreater:
        flags |= BGFX_STATE_DEPTH_TEST_GREATER;
        break;

    case ComparisonOperation::OpNotEqual:
        flags |= BGFX_STATE_DEPTH_TEST_NOTEQUAL;
        break;

    case ComparisonOperation::OpGreaterEqual:
        flags |= BGFX_STATE_DEPTH_TEST_GEQUAL;
        break;

    case ComparisonOperation::OpAlways:
        flags |= BGFX_STATE_DEPTH_TEST_ALWAYS;
        break;
    }

    return flags;
}

U64 EDK::Graphics::GetBgfxCullMode( CullMode mode, TriangleFaceMode trimode )
{
    U64 flag = 0;

    if ( mode == CullMode::CullFront )
    {
        if ( trimode == TriangleFaceMode::FrontByClockWise )
        {
            flag |= BGFX_STATE_CULL_CW;
        }
        else
        {
            flag |= BGFX_STATE_CULL_CCW;
        }
    }
    else if ( mode == CullMode::CullBack )
    {
        if ( trimode == TriangleFaceMode::FrontByClockWise )
        {
            flag |= BGFX_STATE_CULL_CCW;
        }
        else
        {
            flag |= BGFX_STATE_CULL_CW;
        }
    }

    return flag;
}

U64 EDK::Graphics::GetBgfxPrimitiveFlags( InputPrimitives iprim )
{
    U64 flags = 0;

    switch ( iprim )
    {
    case InputPrimitives::LineList:
        flags |= BGFX_STATE_PT_LINES;
        break;

    case InputPrimitives::PointList:
        flags |= BGFX_STATE_PT_POINTS;
        break;

    case InputPrimitives::TriangleList:
        flags |= 0;
        break;

    case InputPrimitives::TriangleStrip:
        flags |= BGFX_STATE_PT_TRISTRIP;
        break;
    }

    return flags;
}

U64 EDK::Graphics::GetBgfxBlendSource( BlendSource bsource )
{
    U64 flags = 0;

    switch ( bsource )
    {
    case BlendSource::BlendZero:
        flags |= BGFX_STATE_BLEND_ZERO;
        break;

    case BlendSource::BlendOne:
        flags |= BGFX_STATE_BLEND_ONE;
        break;

    case BlendSource::BlendSrcColour:
        flags |= BGFX_STATE_BLEND_SRC_COLOR;
        break;

    case BlendSource::BlendInvSrcColour:
        flags |= BGFX_STATE_BLEND_INV_SRC_COLOR;
        break;

    case BlendSource::BlendDestColour:
        flags |= BGFX_STATE_BLEND_DST_COLOR;
        break;

    case BlendSource::BlendInvDestColour:
        flags |= BGFX_STATE_BLEND_INV_DST_COLOR;
        break;

    case BlendSource::BlendFactor:
        flags |= BGFX_STATE_BLEND_FACTOR;
        break;

    case BlendSource::BlendInvBlendFactor:
        flags |= BGFX_STATE_BLEND_INV_FACTOR;
        break;

    case BlendSource::BlendSrcAlpha:
        flags |= BGFX_STATE_BLEND_SRC_ALPHA;
        break;

    case BlendSource::BlendInvSrcAlpha:
        flags |= BGFX_STATE_BLEND_INV_SRC_ALPHA;
        break;

    case BlendSource::BlendDestAlpha:
        flags |= BGFX_STATE_BLEND_DST_ALPHA;
        break;

    case BlendSource::BlendInvDestAlpha:
        flags |= BGFX_STATE_BLEND_INV_DST_ALPHA;
        break;
    }

    return flags;
}

U64 EDK::Graphics::GetBgfxBlendFunc( BlendOperation bop )
{
    U64 flags = 0;

    switch ( bop )
    {
    case BlendOperation::BlendOpAdd:
        flags |= BGFX_STATE_BLEND_EQUATION_ADD;
        break;

    case BlendOperation::BlendOpSubtract:
        flags |= BGFX_STATE_BLEND_EQUATION_SUB;
        break;

    case BlendOperation::BlendOpRevSubtract:
        flags |= BGFX_STATE_BLEND_EQUATION_REVSUB;
        break;

    case BlendOperation::BlendOpMin:
        flags |= BGFX_STATE_BLEND_EQUATION_MIN;
        break;

    case BlendOperation::BlendOpMax:
        flags |= BGFX_STATE_BLEND_EQUATION_MAX;
        break;
    }

    return flags;
}

