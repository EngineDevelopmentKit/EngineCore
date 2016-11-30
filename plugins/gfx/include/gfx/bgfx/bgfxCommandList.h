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
#ifndef __EDK_BGFX_COMMANDLIST_H__
#define __EDK_BGFX_COMMANDLIST_H__

#include "math/scalar/matrix4.h"

#include "common/types.h"

#include "gfx/abstract/gfxCommandList.h"
#include "gfx/abstract/gfxRenderTarget.h"
#include "gfx/abstract/gfxShaderProgram.h"

#include <mutex>
#include <string>

namespace EDK
{
    namespace Graphics
    {
        class BgfxManager;

        class BgfxGraphicsCommandList :
            public GraphicsCommandList
        {
            friend class BgfxManager;
        public:

            BgfxGraphicsCommandList();

            virtual void BeginRecording( const FrameBuffer *rtv, const ViewPort &viewPort, const ClearStrategy &cstrat,
                                         const Matrix4f &viewm, const Matrix4f &projm, const Scissor &scissor );
            virtual void EndRecording();

            virtual void SetVertexBuffer( const VertexBuffer *vb ) override;
            virtual void SetVertexBufferRange( const VertexBuffer *vb, U32 start, U32 num ) override;

            virtual void SetIndexBuffer( const IndexBuffer * ) override;
            virtual void SetIndexBufferRange( const IndexBuffer *, U32 start, U32 num ) override;

            virtual void SetPipelineState( const GraphicsPipelineState *pso ) override;

            virtual void Submit( U32 sortKey = 0 ) override;

        public:

            void Init( const std::string &name );

            // Required by the object pool
            virtual void OnInit() override;
            virtual void OnRelease() override;

        private:

            U32 mDrawCalls;
            std::string mName;
            const GraphicsShaderProgram *mActiveProgram;
        };
    }
}

#endif