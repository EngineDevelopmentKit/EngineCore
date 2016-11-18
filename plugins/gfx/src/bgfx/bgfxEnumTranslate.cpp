#include "gfx/bgfx/bgfxEnumTranslate.h"
#include "gfx/bgfx/bgfxPipelineState.h"
#include "gfx/gfxArchitecture.h"
#include "gfx/abstract/gfxSwapChain.h"
#include "api/console.h"

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


bgfx::Attrib::Enum EDK::Graphics::GetBgfxAttrib( const ShaderAttribute attribute )
{
    switch ( attribute )
    {
    case ShaderAttribute::Position:
        return bgfx::Attrib::Position;

    case ShaderAttribute::Normal:
        return bgfx::Attrib::Normal;

    case ShaderAttribute::Tangent:
        return bgfx::Attrib::Tangent;

    case ShaderAttribute::Bitangent:
        return bgfx::Attrib::Bitangent;

    case ShaderAttribute::Color0:
        return bgfx::Attrib::Color0;

    case ShaderAttribute::Color1:
        return bgfx::Attrib::Color1;

    case ShaderAttribute::Indices:
        return bgfx::Attrib::Indices;

    case ShaderAttribute::Weight:
        return bgfx::Attrib::Weight;

    case ShaderAttribute::TexCoord0:
        return bgfx::Attrib::TexCoord0;

    case ShaderAttribute::TexCoord1:
        return bgfx::Attrib::TexCoord1;

    case ShaderAttribute::TexCoord2:
        return bgfx::Attrib::TexCoord2;

    case ShaderAttribute::TexCoord3:
        return bgfx::Attrib::TexCoord3;

    case ShaderAttribute::TexCoord4:
        return bgfx::Attrib::TexCoord4;

    case ShaderAttribute::TexCoord5:
        return bgfx::Attrib::TexCoord5;

    case ShaderAttribute::TexCoord6:
        return bgfx::Attrib::TexCoord6;

    case ShaderAttribute::TexCoord7:
        return bgfx::Attrib::TexCoord7;
    }
}

bool EDK::Graphics::IsNormalizedAttribType( const AttributeType type )
{
    switch ( type )
    {
    case AttributeType::UINT_NORM_8:
        return true;

    case AttributeType::UINT_NORM_16:
        return true;

    case AttributeType::SINT_NORM_8:
        return true;

    case AttributeType::SINT_NORM_16:
        return true;

    case AttributeType::UINT_NORM_SRGB_8:
        return true;

    default:
        return false;
    }
}

bgfx::AttribType::Enum EDK::Graphics::GetBgfxAttribType( const AttributeType type )
{
    switch ( type )
    {
    case AttributeType::UINT_8:
        return bgfx::AttribType::Enum::Uint8;

    case AttributeType::UINT_NORM_8:
        return bgfx::AttribType::Enum::Uint8;

    case AttributeType::SINT_16:
        return bgfx::AttribType::Enum::Int16;

    case AttributeType::SINT_NORM_16:
        return bgfx::AttribType::Enum::Int16;

    case AttributeType::FLOAT_16:
        return bgfx::AttribType::Enum::Half;

    case AttributeType::FLOAT_32:
        return bgfx::AttribType::Enum::Float;

    default:
        Console::Errorf( "Could not translate an engine attribute type to a bgfx attribute type, unsupported attribute." );
        return bgfx::AttribType::Enum::Float;
    }
}

U32 EDK::Graphics::GetBgfxRenderType( const Interface interf )
{
    switch ( interf )
    {
    case Interface::Direct3D9:
        return bgfx::RendererType::Direct3D9;

    case Interface::Direct3D11:
        return bgfx::RendererType::Direct3D11;

    case Interface::Direct3D12:
        return bgfx::RendererType::Direct3D12;

    case Interface::Metal:
        return bgfx::RendererType::Metal;

    case Interface::Vulkan:
        return bgfx::RendererType::Vulkan;

    case Interface::OpenGL:
        return bgfx::RendererType::OpenGL;

    case Interface::OpenGLES:
        return bgfx::RendererType::OpenGLES;

    default:
        return bgfx::RendererType::Noop;
    }
}

U32 EDK::Graphics::GetBgfxResetFlags( const U32 swapChainFlags )
{
    U32 result = 0;

    if ( IS_SET( swapChainFlags, SwapChainFlags::fullscreen ) )
    {
        result |= BGFX_RESET_FULLSCREEN;
    }

    if ( IS_SET( swapChainFlags, SwapChainFlags::vsync ) )
    {
        result |= BGFX_RESET_VSYNC;
    }

    if ( IS_SET( swapChainFlags, SwapChainFlags::MSAA_2x ) )
    {
        result |= BGFX_RESET_MSAA_X2;
    }

    if ( IS_SET( swapChainFlags, SwapChainFlags::MSAA_4x ) )
    {
        result |= BGFX_RESET_MSAA_X4;
    }

    if ( IS_SET( swapChainFlags, SwapChainFlags::MSAA_8x ) )
    {
        result |= BGFX_RESET_MSAA_X8;
    }

    if ( IS_SET( swapChainFlags, SwapChainFlags::MSAA_16x ) )
    {
        result |= BGFX_RESET_MSAA_X16;
    }

    return result;
}