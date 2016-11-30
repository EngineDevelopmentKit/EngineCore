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
#ifndef __EDK_GFX_BUFFER_DECL_H__
#define __EDK_GFX_BUFFER_DECL_H__

#include "common/types.h"

#include "gfx/gfxFormat.h"

#include <string>
#include <vector>

namespace EDK
{
    namespace Graphics
    {
        enum ShaderAttribute
        {
            Position  = 0x01,
            Normal    = 0x02,
            Tangent   = 0x04,
            Bitangent = 0x08,
            Color0    = 0x10,
            Color1    = 0x20,
            Indices   = 0x40,
            Weight    = 0x80,
            TexCoord0 = 0x100,
            TexCoord1 = 0x200,
            TexCoord2 = 0x400,
            TexCoord3 = 0x800,
            TexCoord4 = 0x1000,
            TexCoord5 = 0x2000,
            TexCoord6 = 0x4000,
            TexCoord7 = 0x8000
        };

        enum class LayoutItemView
        {
            UndefinedLayout = 0,
            Attribute = 1,
            Padding = 2
        };

        struct LayoutData
        {
            ShaderAttribute attribute;
            GpuDataFormat format;
        };

        struct LayoutItem
        {
            LayoutItem();
            LayoutItem( const U32 paddingBytes );
            LayoutItem( const ShaderAttribute &attribute, const GpuDataFormat &format );

            LayoutItemView itemView;

            struct InternalData
            {
                LayoutData layout;
                U32 paddingBytes;
            } data;
        };

        class BufferLayoutDecl
        {
        public:
            BufferLayoutDecl( const U32 alignment = 0 );

            void Add( const ShaderAttribute atribute, const GpuDataFormat &format );
            void Pad( const U32 bytes );

            U32 GetByteSize() const;
            const std::vector< LayoutItem > &GetItems() const;

        private:

            U32 mStride;
            U32 mAlignment;
            U32 mContentFlags;
            std::vector< LayoutItem > mContent;
        };
    }
}

#endif
