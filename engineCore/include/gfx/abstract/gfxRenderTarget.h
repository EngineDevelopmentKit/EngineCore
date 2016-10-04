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
        class FrameBuffer;

        enum class BlendSource
        {
            Blend_Zero = 1,
            Blend_One = 2,
            Blend_src_color = 3,
            Blend_inv_src_color = 4,
            Blend_dest_color = 5,
            Blend_inv_dest_color = 6,
            Blend_blendFactor = 7,
            Blend_inv_blendFactor = 8,
            Blend_src_alpha = 9,
            Blend_inv_src_alpha = 10,
            Blend_dest_alpha = 11,
            Blend_inv_dest_alpha = 12,
        };

        enum class BlendOperation
        {
            BlendOp_add = 1,
            BlendOp_subtract = 2,
            BlendOp_rev_subtract = 3,
            BlendOp_min = 4,
            BlendOp_max = 5
        };

        enum ChannelTarget
        {
            Channel_R = 0x01,
            Channel_G = 0x02,
            Channel_B = 0x04,
            Channel_A = 0x08,
            Channel_RG = ( Channel_R | Channel_G ),
            Channel_RGB = ( Channel_R | Channel_G | Channel_B ),
            Channel_RGBA = ( Channel_R | Channel_G | Channel_B | Channel_A )
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

            FrameBuffer *frameBuffer;
        };


        struct RenderTargetState
        {
            U32 blendStateFlags;

            RenderTarget renderTargets[8];
        };
    }
}

#endif