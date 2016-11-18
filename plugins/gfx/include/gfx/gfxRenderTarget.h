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
#ifndef __EDK_GFX_RENDERTARGET_H__
#define __EDK_GFX_RENDERTARGET_H__

#include "common/types.h"

#define GFX_MAX_RENDERTARGETS 3

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

        enum class ChannelTarget
        {
            ChannelA = 1,
            ChannelRGB = 2,
            ChannelRGBA = 3
        };

        enum BlendStateFlags
        {
            EnableAlphaToCoverage = 0x01
                                    // EnableIndependentBlending = 0x02
        };

        struct RenderTarget
        {
            RenderTarget();

            DataFormat renderTargetFormat;
        };


        struct RenderTargetState
        {
            RenderTargetState();

            U32 blendStateFlags;

            ChannelTarget writeMask;

            BlendSource srcBlendValue;
            BlendSource destBlendValue;
            BlendOperation blendOp;

            BlendSource srcBlendAlpha;
            BlendSource destBlendAlpha;
            BlendOperation alphaBlendOp;

            RenderTarget renderTargets[GFX_MAX_RENDERTARGETS];
        };
    }
}

#endif