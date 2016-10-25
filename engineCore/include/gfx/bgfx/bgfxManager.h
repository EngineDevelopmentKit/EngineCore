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
#ifndef __EDK_BGFX_GRAPHICSMANAGER_H__
#define __EDK_BGFX_GRAPHICSMANAGER_H__

#include "gfx/abstract/gfxManager.h"

#include <mutex>

/// @addtogroup Windows
/// @{

/**
* Manager for the graphics handles.
*
* @sa  Manager
*/

template< typename tBase >
class AbstractObjectPool;

namespace EDK
{
    namespace Graphics
    {
        U32 GetBgfxRenderType( const Interface interf );
        U32 GetBgfxResetFlags( const U32 swapChainFlags );

        class BgfxManager
            : public Graphics::Manager
        {
        public:

            BgfxManager();

            virtual void OnInit() override;
            virtual void OnPostInit() override;
            virtual void OnRelease() override;
            virtual void OnUpdate() override;

            virtual const SwapChain *GetMainWindow() override;

        protected:

            void Reinitialize( const SwapChainDesc &desc, const VideoCard &card, const Interface interf );

            void OnVideoSwitch( const VideoSwitchEvent &e );

        private:

            SwapChain *mMainwindow;
            mutable std::mutex mMutex;
            bool mHasValidInterfaceLink;

            struct VideoState
            {
                VideoState();

                bool dirty;
                VideoCard card;
                Interface interf;
                SwapChainDesc desc;

            } mVideoState;

            AbstractObjectPool< SwapChain > *mSwapChainPool;

        };

    }
}

#endif

