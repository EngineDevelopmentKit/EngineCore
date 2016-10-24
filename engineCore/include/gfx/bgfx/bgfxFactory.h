#pragma once
#ifndef __EDK_BGFX_FACTORY_H__
#define __EDK_BGFX_FACTORY_H__

#include "gfx/abstract/gfxFactory.h"


namespace EDK
{
    namespace Graphics
    {
        enum Interface;
        class VideoCard;

        class BgfxFactory : public Factory
        {
        public:

            

        protected:



        private:

            bool mGeneratedMainWindow;

            AbstractObjectPool< SwapChain > *mSwapChainPool;
        };
    }
}

#endif