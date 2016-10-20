#pragma once
#ifndef __EDK_BGFX_FACTORY_H__
#define __EDK_BGFX_FACTORY_H__

#include "gfx/abstract/gfxFactory.h"

template< typename tBase >
class AbstractObjectPool;

namespace EDK
{
    namespace Graphics
    {
        enum Interface;
        class VideoCard;

        class BgfxFactory : public Factory
        {
        public:

            BgfxFactory( const VideoCard &card, Interface igfx );

            virtual void Release() override;

            virtual SwapChain *CreateSwapChain( const SwapChainDesc &desc ) override;


        protected:



        private:

            bool mGeneratedMainWindow;

            AbstractObjectPool< SwapChain > *mSwapChainPool;
        };
    }
}

#endif