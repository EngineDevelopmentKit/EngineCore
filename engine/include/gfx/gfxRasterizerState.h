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

        enum InputPrimitives
        {
            PointList = 1,
            LineList = 2,
            TriangleList = 3
        };

        struct RasterizerState
        {
            RasterizerState();

            FillMode fillMode;
            CullMode cullMode;
            TriangleFaceMode faceMode;
            InputPrimitives inputLayout;

            U32 msaaSamples;

            bool lineAntiAliasing;
        };

    }
}

#endif