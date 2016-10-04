/**
* @cond ___LICENSE___
*
* Copyright (c) 2016 Koen Visscher, Paul Visscher, Andrew Mac and individual contributors.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
* @endcond
*/

#pragma once
#ifndef __EDK_GFX_PIPELINE_STATE_H__
#define __EDK_GFX_PIPELINE_STATE_H__

#include "common/types.h"

namespace EDK
{
    namespace Graphics
    {
        enum class DataFormat;

        enum class BlendSource
        {
            BlendZero = 1,
            BlendOne = 2,
            BlendSrcColour = 3,
            BlendInvSrcColour = 4,
            BlendDestColour = 5,
            BlendInvDestColour = 6,
            BlendFactor = 7,
            BlendInvBlendFactor = 8,
            BlendSrcAlpha = 9,
            BlendInvSrcAlpha = 10,
            BlendDestAlpha = 11,
            BlendInvDestAlpha = 12,
        };

        enum class BlendOperation
        {
            BlendOpAdd = 1,
            BlendOpSubtract = 2,
            BlendOpRevSubtract = 3,
            BlendOpMin = 4,
            BlendOpMax = 5
        };

        enum ChannelTarget
        {
            ChannelR = 0x01,
            ChannelG = 0x02,
            ChannelB = 0x04,
            ChannelA = 0x08,
            ChannelRG = ( ChannelR | ChannelG ),
            ChannelRGB = ( ChannelR | ChannelG | ChannelB ),
            ChannelRGBA = ( ChannelR | ChannelG | ChannelB | ChannelA )
        };

        enum BlendStateFlags
        {
            EnableBlending = 0x01,
            EnableAlphaToCoverage = 0x02,
            EnableIndependentBlending = 0x04
        };

        struct RenderTarget
        {
            BlendSource srcBlendValue;
            BlendSource destBlendValue;
            BlendOperation blendOp;

            BlendSource srcBlendAlpha;
            BlendSource destBlendAlpha;
            BlendOperation alphaBlendOp;

            ChannelTarget writeMask;

            DataFormat renderTargetFormat;
        };


        struct RenderTargetState
        {
            U32 blendStateFlags;
            U32 numRenderTargets;

            RenderTarget renderTargets[8];
        };
    }
}

#endif