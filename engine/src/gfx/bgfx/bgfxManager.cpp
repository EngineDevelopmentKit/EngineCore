#include "gfx/bgfx/bgfxManager.h"
#include "gfx/bgfx/bgfxSwapChain.h"

#include "common/util.h"

#include "manager/eventManager.h"
#include "manager/poolManager.h"

#include <bgfx/bgfxplatform.h>


EDK::Graphics::BgfxManager::BgfxManager() :
    mMainwindow( nullptr ), mHasValidInterfaceLink( false ), mSwapChainPool( nullptr )
{

}

EDK::Graphics::BgfxManager::VideoState::VideoState() :
    dirty( false )
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
    if ( mMainwindow )
    {
        mSwapChainPool->Dispose( mMainwindow );
    }

    ManagerHolder *const holder = SystemManager::Get()->GetManagers();
    PoolManager *const poolMngr = holder->pool;

    poolMngr->Remove< BgfxSwapChain >();

    Unobserve< BgfxManager, VideoSwitchEvent >( &BgfxManager::OnVideoSwitch );

    // release bgfx
    bgfx::shutdown();
}

void EDK::Graphics::BgfxManager::OnUpdate()
{
    if ( mVideoState.dirty )
    {
        Reinitialize( mVideoState.desc, mVideoState.card, mVideoState.interf );
    }
}

const EDK::Graphics::VertexBuffer *EDK::Graphics::BgfxManager::CreateVertexBuffer( const VertexBufferDesc &desc )
{
    std::lock_guard<std::mutex> lock( mMutex );


}

const EDK::Graphics::SwapChain *EDK::Graphics::BgfxManager::GetMainWindow()
{
    return mMainwindow;
}

bgfx::VertexDecl EDK::Graphics::GetBgfxVertexDecl( const BufferLayoutDecl &layout )
{
    bgfx::VertexDecl vertexDecl;
    vertexDecl.begin();

    for ( const BufferLayoutDecl::LayoutItem &item : layout.GetItems() )
    {
        if ( item.itemView == BufferLayoutDecl::LayoutItem::LayoutItemView::Padding )
        {
            vertexDecl.skip( item.data.paddingBytes );
        }
        else if ( item.itemView == BufferLayoutDecl::LayoutItem::LayoutItemView::Attribute )
        {

        }
    }

    vertexDecl.end();

    return vertexDecl;
}

bgfx::Attrib EDK::Graphics::GetBgfxAttrib( const ShaderAttribute attribute )
{
    switch ( attribute )
    {
    case ShaderAttribute::Position:
    case ShaderAttribute::Normal:
    case ShaderAttribute::Tangent:
    case ShaderAttribute::Bitangent:
    case ShaderAttribute::Color0:
    case ShaderAttribute::Color1:
    case ShaderAttribute::Indices:
    case ShaderAttribute::Weight:
    case ShaderAttribute::TexCoord0:
    case ShaderAttribute::TexCoord1:
    case ShaderAttribute::TexCoord2:
    case ShaderAttribute::TexCoord3:
    case ShaderAttribute::TexCoord4:
    case ShaderAttribute::TexCoord5:
    case ShaderAttribute::TexCoord6:
    case ShaderAttribute::TexCoord7:
    }
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

U32 EDK::Graphics::GetBgfxResetFlags( const U32 swapChainFlags )
{
    U32 result = 0;

    if ( IS_SET( swapChainFlags, SwapChainFlags::fullscreen ) )
    {
        result |= BGFX_RESET_FULLSCREEN;
    }

    if ( IS_SET( swapChainFlags, SwapChainFlags::vsync ) )
    {
        result |= BGFX_RESET_VSYNC;
    }

    if ( IS_SET( swapChainFlags, SwapChainFlags::MSAA_2x ) )
    {
        result |= BGFX_RESET_MSAA_X2;
    }

    if ( IS_SET( swapChainFlags, SwapChainFlags::MSAA_4x ) )
    {
        result |= BGFX_RESET_MSAA_X4;
    }

    if ( IS_SET( swapChainFlags, SwapChainFlags::MSAA_8x ) )
    {
        result |= BGFX_RESET_MSAA_X8;
    }

    if ( IS_SET( swapChainFlags, SwapChainFlags::MSAA_16x ) )
    {
        result |= BGFX_RESET_MSAA_X16;
    }

    return result;
}

void EDK::Graphics::BgfxManager::Reinitialize( const SwapChainDesc &desc, const VideoCard &card,
                                               const Interface interf )
{
    std::lock_guard<std::mutex> lock( mMutex );

    // release current main window
    if ( mMainwindow )
    {
        mSwapChainPool->Dispose( mMainwindow );
    }

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

    U32 bgfxReset = GetBgfxResetFlags( desc.swapChainFlags );

    bgfx::reset( desc.size[0], desc.size[1], bgfxReset );

    mMainwindow = mSwapChainPool->Get();
    static_cast<BgfxSwapChain *>( mMainwindow )->Init( nullptr, desc );

    mHasValidInterfaceLink = true;
}

void EDK::Graphics::BgfxManager::OnVideoSwitch( const VideoSwitchEvent &e )
{
    // Cant just do the reinit directly in a threaded environment, soo
    // We queue it

    std::lock_guard<std::mutex> lock( mMutex );

    mVideoState.card = e.videocard;
    mVideoState.desc = e.mainwindow;
    mVideoState.interf = e.interface;
    mVideoState.dirty = true;
}