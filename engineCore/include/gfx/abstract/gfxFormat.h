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

namespace EDK
{
    namespace Graphics
    {
        enum class DataFormat
        {
            //mapping as d3d
            Format_unknown = 0,
            Format_RGBA_32_F = 1,
            Format_RGBA_32_U = 2,
            Format_RGBA_32_S = 3,
            Format_RGB_32_F = 4,
            Format_RGB_32_U = 5,
            Format_RGB_32_S = 6,
            Format_RG_32_F = 7,
            Format_RG_32_U = 8,
            Format_RG_32_S = 9,
            Format_R_32_F = 10,
            Format_R_32_U = 11,
            Format_R_32_S = 12,
            Format_RGBA_16_F = 13,
            Format_RGBA_16_U = 14,
            Format_RGBA_16_S = 15,
            Format_RGBA_16_UNORM = 16,
            Format_RGBA_16_SNORM = 17,
            Format_RG_16_F = 18,
            Format_RG_16_U = 19,
            Format_RG_16_S = 20,
            Format_RG_16_UNORM = 21,
            Format_RG_16_SNORM = 22,
            Format_R_16_F = 23,
            Format_R_16_U = 24,
            Format_R_16_S = 25,
            Format_R_16_UNORM = 26,
            Format_R_16_SNORM = 27,
            Format_RGB_10_A_2_UNORM = 28,
            Format_RGB_10_A_2_U = 29,
            Format_RGBA_8_U = 30,
            Format_RGBA_8_S = 31,
            Format_RGBA_8_UNORM = 32,
            Format_RGBA_8_UNORM_SRGB = 33,
            Format_RGBA_8_SNORM = 34,
            Format_RG_8_U = 35,
            Format_RG_8_S = 36,
            Format_RG_8_UNORM = 37,
            Format_RG_8_SNORM = 38,
            Format_R_8_U = 39,
            Format_R_8_S = 40,
            Format_R_8_UNORM = 41,
            Format_R_8_SNORM = 42,
            Format_BC1_UNORM = 43,
            Format_BC1_UNORM_SRGB = 44,
            Format_BC2_UNORM = 45,
            Format_BC2_UNORM_SRGB = 46,
            Format_BC3_UNORM = 47,
            Format_BC3_UNORM_SRGB = 48,
            Format_BC4_UNORM = 49,
            Format_BC4_SNORM = 50,
            Format_BC5_UNORM = 51,
            Format_BC5_SNORM = 52,
            Format_BC7_UNORM = 53,
            Format_BC7_UNORM_SRGB = 54,
            Format_R24S8 = 55,

            // Special legacy crap :(
            Format_BGRA_8_UNORM = 56,
            Format_BGRA_8_UNORM_SRGB = 57,

            Format_STRUCTURED = 58
        };
    }
}

#endif