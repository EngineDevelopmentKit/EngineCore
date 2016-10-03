#pragma once
#ifndef __EDK_GFX_ADAPTER_H__
#define __EDK_GFX_ADAPTER_H__

#include "common/types.h"

#include <string>
#include <vector>

namespace EDK
{
    namespace GFX
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
