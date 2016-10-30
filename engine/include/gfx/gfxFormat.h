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
#ifndef __EDK_GFX_FORMAT_H__
#define __EDK_GFX_FORMAT_H__

#include "common/types.h"

namespace EDK
{
    namespace Graphics
    {
        enum class DataFormatView
        {
            RGBA = 1,
            Compressed = 2,
            Special = 3
        };

        enum class AtributeType
        {
            UINT_8 = 1,
            UINT_16 = 2,
            UINT_32 = 3,
            SINT_8 = 4,
            SINT_16 = 5,
            SINT_32 = 6,
            Float_16 = 7,
            Float_32 = 8,
            UINT_NORM_8 = 9,
            UINT_NORM_16 = 10,
            SINT_NORM_8 = 11,
            SINT_NORM_16 = 12,
            UINT_NORM_SRGB_8 = 13,
        };

        enum class CompressedDataFormat
        {
            Format_BC1_UNORM = 1,
            Format_BC1_UNORM_SRGB = 2,
            Format_BC2_UNORM = 3,
            Format_BC2_UNORM_SRGB = 4,
            Format_BC3_UNORM = 5,
            Format_BC3_UNORM_SRGB = 6,
            Format_BC4_UNORM = 7,
            Format_BC4_SNORM = 8,
            Format_BC5_UNORM = 9,
            Format_BC5_SNORM = 10,
            Format_BC7_UNORM = 11,
            Format_BC7_UNORM_SRGB = 12
        };

        enum class SpecialDataFormat
        {
            R24S8 = 27,
            RGB_10_A_2_UINT = 28,
            RGB_10_A_2_UINT_NORM = 29,
        };

        struct GpuDataFormat
        {
            DataFormatView formatView;

            union
            {
                struct
                {
                    U32 elements;
                    AtributeType type;

                } rgbaView;

                CompressedDataFormat compressedFormat;
                SpecialDataFormat specialFormat;

            } data;

            U32 GetByteSize() const;
        };
    }
}

#endif