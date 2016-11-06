#pragma once
#ifndef __EDK_GFX_DEPTH_STENCIL_STATE_H__
#define __EDK_GFX_DEPTH_STENCIL_STATE_H__

#include "common/types.h"
#include "gfx/gfxFormat.h"

namespace EDK
{
    namespace Graphics
    {
        enum ComparisonOperation
        {
            OpNever = 1,
            OpLess = 2,
            OpEqual = 3,
            OpLessEqual = 4,
            OpGreater = 5,
            OpNotEqual = 6,
            OpGreaterEqual = 7,
            OpAlways = 8
        };

        enum StencilOperation
        {
            StencilOpKeep = 1,
            StencilOpZero = 2,
            StencilOpReplace = 3,
            StencilOpIncr = 4,
            StencilOpIncrSat = 5,
            StencilOpDecr = 6,
            StencilOpDecrSat = 7,
            StencilOpInvert = 8
        };

        struct StencilTest
        {
            StencilTest();

            StencilOperation onStencilFail;
            StencilOperation onStencilPassDepthFail;
            StencilOperation onStencilDepthPass;
            ComparisonOperation stencilCompareOp;
        };

        struct DepthStencilState
        {
            DepthStencilState();

            bool enableDepthTest;
            bool enableStencilTest;
            bool enableDepthWrite;

            U8 stencilWriteMask;
            U8 stencilReadMask;

            F32 depthBias;
            F32 depthBiasClamp;
            F32 slopeScaledDepthBias;

            GpuDataFormat depthBufferFormat;

            ComparisonOperation depthTestOp;

            StencilTest backFaceStencilTest;
            StencilTest frontFaceStencilTest;
        };
    }
}

#endif