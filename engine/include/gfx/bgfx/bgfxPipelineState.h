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
#ifndef __EDK_BGFX_PIPELINE_STATE_H__
#define __EDK_BGFX_PIPELINE_STATE_H__

#include "gfx/abstract/gfxPipelineState.h"

namespace EDK
{
    namespace Graphics
    {
        class BgfxPipelineState : public PipelineState
        {
            friend class BgfxManager;
        public:

            BgfxPipelineState();

        public:

            // Required by the object pool
            virtual void OnInit() override;
            virtual void OnRelease() override;

        protected:

            void Init( const PipelineStateDesc &desce );

        private:

            PipelineStateDesc mDesc;
        };
    }
}

#endif