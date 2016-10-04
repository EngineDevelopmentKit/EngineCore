#pragma once
#ifndef __EDK_GFX_RASTERIZER_STATE_H__
#define __EDK_GFX_RASTERIZER_STATE_H__

#include "common/types.h"

namespace EDK
{
    namespace Graphics
    {
        enum FillMode
        {
            FillSolid = 1,
            FillWireFrame = 2
        };

        enum CullMode
        {
            CullFront = 1,
            CullBack = 2,
            CullNone = 3
        };

        enum TriangleFaceMode
        {
            FrontByClockWise = 1,
            FrontByCounterClockWise = 2
        };

        struct RasterizerState
        {
            FillMode fillMode;
            CullMode cullMode;
            TriangleFaceMode faceMode;

            bool lineAntiAliasing;
        };

    }
}

#endif