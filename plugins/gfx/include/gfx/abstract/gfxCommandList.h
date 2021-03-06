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
#ifndef __EDK_GFX_COMMANDLIST_H__
#define __EDK_GFX_COMMANDLIST_H__

#include "math/scalar/matrix4.h"

namespace EDK
{
    namespace Graphics
    {
        struct Scissor;
        struct ViewPort;
        struct ClearStrategy;

        class FrameBuffer;
        class IndexBuffer;
        class VertexBuffer;
        class GraphicsPipelineState;

        class CommandList
        {
        public:

            virtual ~CommandList() {}

        public:

            // Required by the object pool
            virtual void OnInit() = 0;
            virtual void OnRelease() = 0;
        };

        class GraphicsCommandList :
            public CommandList
        {
        public:

            virtual ~GraphicsCommandList() {}

            virtual void BeginRecording( const FrameBuffer *rtv, const ViewPort &viewPort, const ClearStrategy &cstrat,
                                         const Matrix4f &viewm, const Matrix4f &projm, const Scissor &scissor ) = 0;
            virtual void EndRecording() = 0;

            virtual void SetVertexBuffer( const VertexBuffer * ) = 0;
            virtual void SetVertexBufferRange( const VertexBuffer *vb, U32 start, U32 num ) = 0;

            virtual void SetIndexBuffer( const IndexBuffer * ) = 0;
            virtual void SetIndexBufferRange( const IndexBuffer *, U32 start, U32 num ) = 0;

            virtual void SetPipelineState( const GraphicsPipelineState *pso ) = 0;

            virtual void Submit( const Matrix4f *matrices, U32 numMatrices = 1, U32 sortKey = 0 ) = 0;
        };

        class ComputeCommandList :
            public CommandList
        {
        public:

            virtual ~ComputeCommandList() {}
        };
    }
}

#endif