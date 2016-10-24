#pragma once
#ifndef __EDK_GFX_FACTORY_H__
#define __EDK_GFX_FACTORY_H__

namespace EDK
{
    namespace Graphics
    {
        class SwapChain;

        struct SwapChainDesc;

        class Factory
        {
        public:

            virtual ~Factory() {}

            virtual void Release() = 0;

            virtual SwapChain *CreateSwapChain( const SwapChainDesc &desc ) = 0;


        };
    }
}

#endif