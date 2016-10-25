#include "gfx/bgfx/bgfxManager.h"
#include "gfx/bgfx/bgfxSwapChain.h"

#include "manager/eventManager.h"
#include "manager/poolManager.h"

#include <bgfx/bgfxplatform.h>
#include <bgfx/bgfx.h>

/*
EDK::Graphics::BgfxFactory::BgfxFactory( const VideoCard &card, Interface igfx ) :
    mGeneratedMainWindow( false ), mSwapChainPool( nullptr )
{
    ManagerHolder *const holder = SystemManager::Get()->GetManagers();
    PoolManager *const poolMngr = holder->pool;

    mSwapChainPool = poolMngr->Add< BgfxSwapChain, SwapChain  >();
}
*/

/*
void EDK::Graphics::BgfxFactory::Release()
{
    ManagerHolder *const holder = SystemManager::Get()->GetManagers();
    PoolManager *const poolMngr = holder->pool;

    poolMngr->Remove< BgfxSwapChain >();
}
*/

EDK::Graphics::BgfxManager::BgfxManager() :
    mMainwindow( nullptr ), mHasValidInterfaceLink( false ), mSwapChainPool( nullptr )
{

}

void EDK::Graphics::BgfxManager::OnInit()
{
    ManagerHolder *const holder = SystemManager::Get()->GetManagers();
    PoolManager *const poolMngr = holder->pool;

    mSwapChainPool = poolMngr->Add< BgfxSwapChain, SwapChain  >();

    Observe < BgfxManager, VideoSwitchEvent >( &BgfxManager::OnVideoSwitch );
}

void EDK::Graphics::BgfxManager::OnPostInit()
{

}

void EDK::Graphics::BgfxManager::OnRelease()
{
    ManagerHolder *const holder = SystemManager::Get()->GetManagers();
    PoolManager *const poolMngr = holder->pool;

    poolMngr->Remove< BgfxSwapChain >();

    Unobserve< BgfxManager, VideoSwitchEvent >( &BgfxManager::OnVideoSwitch );
}

void EDK::Graphics::BgfxManager::OnUpdate()
{

}

EDK::Graphics::SwapChain *EDK::Graphics::BgfxManager::CreateSwapChain( const SwapChainDesc &desc )
{
    std::lock_guard<std::mutex> lock( mMutex );

    BgfxSwapChain *swapChain = nullptr;

    if ( mSwapChainPool )
    {
        bgfx::FrameBufferHandle *fbh = nullptr;

        swapChain = static_cast<BgfxSwapChain *>( mSwapChainPool->Get() );
        swapChain->Init( nullptr, desc );
    }

    return swapChain;
}


U32 EDK::Graphics::GetBgfxRenderType( const Interface interf )
{
    switch ( interf )
    {
    case Interface::Direct3D9:
        return bgfx::RendererType::Direct3D9;

    case Interface::Direct3D11:
        return bgfx::RendererType::Direct3D11;

    case Interface::Direct3D12:
        return bgfx::RendererType::Direct3D12;

    case Interface::Metal:
        return bgfx::RendererType::Metal;

    case Interface::Vulkan:
        return bgfx::RendererType::Vulkan;

    case Interface::OpenGL:
        return bgfx::RendererType::OpenGL;

    case Interface::OpenGLES:
        return bgfx::RendererType::OpenGLES;

    default:
        return bgfx::RendererType::Noop;
    }
}

void EDK::Graphics::BgfxManager::Reinitialize( const SwapChainDesc &desc, const VideoCard &card,
                                               const Interface interf )
{
    std::lock_guard<std::mutex> lock( mMutex );

    // set the platform data
    bgfx::PlatformData pd;
    pd.ndt = desc.ndh;
    pd.nwh = desc.hwnd;
    pd.context = NULL;
    pd.backBuffer = NULL;
    pd.backBufferDS = NULL;
    bgfx::setPlatformData( pd );

    // TODO add gpu support here!
    bgfx::init( static_cast<bgfx::RendererType::Enum>( GetBgfxRenderType( interf ) ) );

    mHasValidInterfaceLink = true;
}

void EDK::Graphics::BgfxManager::OnVideoSwitch( const VideoSwitchEvent &e )
{
    Reinitialize( e.mainwindow, e.videocard, e.interface );
}