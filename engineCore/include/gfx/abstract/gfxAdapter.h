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
#ifndef __EDK_GFX_ADAPTER_H__
#define __EDK_GFX_ADAPTER_H__

#include "common/types.h"

#include <string>
#include <vector>

namespace EDK
{
    namespace Graphics
    {
        struct DisplayMode
        {
            U32 width;
            U32 height;
            U32 numerator;
            U32 denominator;
        };

        struct VideoCardOutput
        {
            std::wstring desc;
            U32 index;

            std::vector< DisplayMode > displayModes;
        };

        struct VideoCard
        {
            std::wstring desc;
            U32 index;
            U32 vendorId;
            U32 deviceId;
            U32 subSysId;
            U32 revision;
            size_t vram;
            size_t sysram;
            size_t sharedram;

            U64 capabilityFlags;

            std::vector< VideoCardOutput > outputs;
        };
    }
}

#endif
