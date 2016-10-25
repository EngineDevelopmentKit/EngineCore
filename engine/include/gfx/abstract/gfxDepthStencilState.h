#pragma once
#ifndef __EDK_GFX_DEPTH_STENCIL_STATE_H__
#define __EDK_GFX_DEPTH_STENCIL_STATE_H__

#include "common/types.h"

namespace EDK
{
    namespace Graphics
    {
        enum class DataFormat;

        enum ComparisonOperation
        {
            DepthOpNever = 1,
            DepthOpLess = 2,
            DepthOpEqual = 3,
            DepthOpLessEqual = 4,
            DepthOpGreater = 5,
            DepthOpNotEqual = 6,
            DepthOpGreaterEqual = 7,
            DepthOpAlways = 8
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
            StencilOperation onStencilFail;
            StencilOperation onStencilPassDepthFail;
            StencilOperation onStencilDepthPass;
            ComparisonOperation stencilCompareOp;
        };

        struct DepthStencilState
        {
            bool enableDepthTest;
            bool enableStencilTest;
            bool enableDepthWrite;

            U8 stencilWriteMask;
            U8 stencilReadMask;

            F32 depthBias;
            F32 depthBiasClamp;
            F32 slopeScaledDepthBias;

            DataFormat depthBufferFormat;

            ComparisonOperation depthTestOp;

            StencilTest backFaceStencilTest;
            StencilTest frontFaceStencilTest;
        };
    }
}

#endif