#pragma once
#ifndef __EDK_GFX_DEPTH_STENCIL_STATE_H__
#define __EDK_GFX_DEPTH_STENCIL_STATE_H__

#include "common/types.h"

namespace EDK
{
    namespace Graphics
    {
        enum DepthCompareOperation
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

        struct DepthStencilState
        {
            bool enableDepthTest;
            bool enableStencilTest;
            bool enableDepthWrite;

            U8 stencilWriteMask;
            U8 stencilReadMask;

            DepthCompareOperation depthTestOp;


        };
    }
}

#endif