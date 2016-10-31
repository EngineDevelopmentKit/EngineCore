#include "gfx/bgfx/bgfxManager.h"
#include "gfx/bgfx/bgfxSwapChain.h"

#include "common/util.h"
#include "api/console.h"

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
           if ( item.data.format.formatView != DataFormatView::RGBA )
           {
               Console::Errorf( "Tried to process a bgfx layout item, where the data format is not RGBA");
               
               vertexDecl.skip( item.data.format.GetByteSize() );
           } 
           else
           {
               const bgfx::Attrib::Enum bgfxAttrib = GetBgfxAttrib( item.data.attribute );
               const bgfx::AttribType::Enum bgfxAttribType = GetBgfxAttribType( item.data.format.data.rgbaView.type );
               const bool isNormalized = IsNormalizedAttribType( item.data.format.data.rgbaView.type );
               const U32 numelements = item.data.format.data.rgbaView.elements;
               
               vertexDecl.add( bgfxAttrib, numelements, bgfxAttribType, isNormalized, false );
           }
        }
    }

    vertexDecl.end();

    return vertexDecl;
}

bgfx::Attrib::Enum EDK::Graphics::GetBgfxAttrib( const ShaderAttribute attribute )
{
    switch ( attribute )
    {
    case ShaderAttribute::Position:
        return bgfx::Attrib::Position;
    case ShaderAttribute::Normal:
        return bgfx::Attrib::Normal;
    case ShaderAttribute::Tangent:
        return bgfx::Attrib::Tangent;
    case ShaderAttribute::Bitangent:
        return bgfx::Attrib::Bitangent;
    case ShaderAttribute::Color0:
        return bgfx::Attrib::Color0;
    case ShaderAttribute::Color1:
        return bgfx::Attrib::Color1;
    case ShaderAttribute::Indices:
        return bgfx::Attrib::Indices;
    case ShaderAttribute::Weight:
        return bgfx::Attrib::Weight;
    case ShaderAttribute::TexCoord0:
        return bgfx::Attrib::TexCoord0;
    case ShaderAttribute::TexCoord1:
        return bgfx::Attrib::TexCoord1;
    case ShaderAttribute::TexCoord2:
        return bgfx::Attrib::TexCoord2;
    case ShaderAttribute::TexCoord3:
        return bgfx::Attrib::TexCoord3;
    case ShaderAttribute::TexCoord4:
        return bgfx::Attrib::TexCoord4;
    case ShaderAttribute::TexCoord5:
        return bgfx::Attrib::TexCoord5;
    case ShaderAttribute::TexCoord6:
        return bgfx::Attrib::TexCoord6;
    case ShaderAttribute::TexCoord7:
        return bgfx::Attrib::TexCoord7;
    }
}

bool EDK::Graphics::IsNormalizedAttribType( const AtributeType type )
{
    switch( type )
    {
        case AtributeType::UINT_NORM_8:  
        case AtributeType::UINT_NORM_16:
        case AtributeType::SINT_NORM_8:
        case AtributeType::SINT_NORM_16:
        case AtributeType::UINT_NORM_SRGB_8:
        
        default:
            return false;
    }
    
    return true;
}

bgfx::AttribType::Enum EDK::Graphics::GetBgfxAttribType( const AtributeType type )
{
    switch( type )
    {
    case AtributeType::UINT_8:
        return bgfx::AttribType::Enum::Uint8;
    case AtributeType::UINT_NORM_8:
        return bgfx::AttribType::Enum::Uint8;
    case AtributeType::SINT_16:
        return bgfx::AttribType::Enum::Int16;
    case AtributeType::SINT_NORM_16:
        return bgfx::AttribType::Enum::Int16;
    case AtributeType::Float_16:
        return bgfx::AttribType::Enum::Half;
    case AtributeType::Float_32:
        return bgfx::AttribType::Enum::Float;
    default:
        Console::Errorf("Could not translate an engine attribute type to a bgfx attribute type, unsupported attribute.");
        return bgfx::AttribType::Enum::Float;
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