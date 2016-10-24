#include "gfx/bgfx/bgfxFactory.h"
#include "gfx/bgfx/bgfxSwapChain.h"

#include "manager/poolManager.h"

#include <bgfx/bgfxplatform.h>

EDK::Graphics::BgfxFactory::BgfxFactory( const VideoCard &card, Interface igfx ) :
    mGeneratedMainWindow( false ), mSwapChainPool( nullptr )
{
    ManagerHolder *const holder = SystemManager::Get()->GetManagers();
    PoolManager *const poolMngr = holder->pool;

    mSwapChainPool = poolMngr->Add< BgfxSwapChain, SwapChain  >();
}

void EDK::Graphics::BgfxFactory::Release()
{
    ManagerHolder *const holder = SystemManager::Get()->GetManagers();
    PoolManager *const poolMngr = holder->pool;

    poolMngr->Remove< BgfxSwapChain >();
}

EDK::Graphics::SwapChain *EDK::Graphics::BgfxFactory::CreateSwapChain( const SwapChainDesc &desc )
{
    BgfxSwapChain *swapChain = nullptr;

    if ( mSwapChainPool )
    {
        bgfx::FrameBufferHandle *fbh = nullptr;

        if ( !mGeneratedMainWindow )
        {
            bgfx::PlatformData pd;
            pd.ndt = desc.ndh;
            pd.nwh = desc.hwnd;
            pd.context = NULL;
            pd.backBuffer = NULL;
            pd.backBufferDS = NULL;
            bgfx::setPlatformData( pd );

            mGeneratedMainWindow = true;
        }
        else
        {
            // TODO
        }

        swapChain = static_cast<BgfxSwapChain *>( mSwapChainPool->Get() );
        swapChain->Init( nullptr, desc );
    }

    return swapChain;
}