#include "gfx/bgfx/bgfxManager.h"
#include "gfx/bgfx/bgfxSwapChain.h"
#include "gfx/bgfx/bgfxShaderBlob.h"
#include "gfx/bgfx/bgfxCommandList.h"
#include "gfx/bgfx/bgfxIndexBuffer.h"
#include "gfx/bgfx/bgfxVertexBuffer.h"
#include "gfx/bgfx/bgfxPipelineState.h"
#include "gfx/bgfx/bgfxShaderProgram.h"

#include "common/util.h"
#include "api/console.h"

#include "manager/eventManager.h"
#include "manager/poolManager.h"

#include <bx/bx.h>
#include <bx/fpumath.h>
#include <bgfx/bgfxplatform.h>


EDK::Graphics::BgfxManager::BgfxManager() :
    mMainwindow( nullptr ), mHasValidInterfaceLink( false ),
    mSwapChainPool( nullptr ), mVertexBufferPool( nullptr )
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

    mSwapChainPool = poolMngr->Add< BgfxSwapChain, SwapChain >();
    mShaderBlobPool = poolMngr->Add< BgfxShaderBlob, ShaderBlob >();
    mIndexBufferPool = poolMngr->Add< BgfxIndexBuffer, IndexBuffer >();
    mVertexBufferPool = poolMngr->Add< BgfxVertexBuffer, VertexBuffer >();
    mShaderProgramPool = poolMngr->Add< BgfxShaderProgram, ShaderProgram >();
    mPipelineStatePool = poolMngr->Add< BgfxGraphicsPipelineState, GraphicsPipelineState >();
    mGraphicsCommandListPool = poolMngr->Add< BgfxGraphicsCommandList, GraphicsCommandList >();

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
    poolMngr->Remove< BgfxShaderBlob >();
    poolMngr->Remove< BgfxIndexBuffer >();
    poolMngr->Remove< BgfxVertexBuffer >();
    poolMngr->Remove< BgfxShaderProgram >();
    poolMngr->Remove< BgfxGraphicsCommandList >();
    poolMngr->Remove< BgfxGraphicsPipelineState >();

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

    if ( mMainwindow )
    {
        mMainwindow->Present();
    }
}

Matrix4f EDK::Graphics::BgfxManager::LookAtMatrix( const Vec3f &eye, const Vec3f &at ) const
{
    Matrix4f mat;
    bx::mtxLookAt( mat.Data(), eye.Data(), at.Data() );

    return mat;
}

Matrix4f EDK::Graphics::BgfxManager::ProjMatrix( F32 fov, U32 width, U32 height, F32 near, F32 far ) const
{
    Matrix4f mat;
    bx::mtxProj( mat.Data(), fov, float( width ) / float( height ), near, far );

    return mat;
}

const EDK::Graphics::PixelShaderBlob *EDK::Graphics::BgfxManager::CreatePixelShaderBlob( void *memory, size_t memSize )
{
    std::lock_guard<std::mutex> lock( mMutex );

    bgfx::ShaderHandle sh = bgfx::createShader( bgfx::makeRef( memory, memSize ) );

    PixelShaderBlob *shader = mShaderBlobPool->Get();
    static_cast<BgfxShaderBlob *>( shader )->Init( ShaderReflection(), sh );

    return shader;
}

const EDK::Graphics::VertexShaderBlob *EDK::Graphics::BgfxManager::CreateVertexShaderBlob( void *memory,
                                                                                           size_t memSize )
{
    std::lock_guard<std::mutex> lock( mMutex );

    bgfx::ShaderHandle sh = bgfx::createShader( bgfx::makeRef( memory, memSize ) );

    PixelShaderBlob *shader = mShaderBlobPool->Get();
    static_cast<BgfxShaderBlob *>( shader )->Init( ShaderReflection(), sh );

    return shader;
}

const EDK::Graphics::IndexBuffer *EDK::Graphics::BgfxManager::CreateIndexBuffer( const IndexBufferDesc &desc,
                                                                                 void *memory, size_t memSize )
{
    std::lock_guard<std::mutex> lock( mMutex );

    U32 bgfxFlags = desc.type == AttributeType::UINT_32 ? BGFX_BUFFER_INDEX32 : 0;

    bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer( bgfx::makeRef( memory, memSize ), bgfxFlags );

    IndexBuffer *ib = mIndexBufferPool->Get();
    static_cast<BgfxIndexBuffer *>( ib )->Init( desc, ibh );

    return ib;
}

const EDK::Graphics::VertexBuffer *EDK::Graphics::BgfxManager::CreateVertexBuffer( const VertexBufferDesc &desc,
                                                                                   void *memory, size_t memSize )
{
    std::lock_guard<std::mutex> lock( mMutex );

    bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer( bgfx::makeRef( memory, memSize ),
                                                             GetBgfxVertexDecl( desc.layoutDecl ) );

    VertexBuffer *vb = mVertexBufferPool->Get();
    static_cast<BgfxVertexBuffer *>( vb )->Init( desc, vbh );

    return vb;
}

const EDK::Graphics::GraphicsPipelineState *EDK::Graphics::BgfxManager::CreatePipelineState(
    const GraphicsPipelineStateDesc &desc,
    const GraphicsShaderProgram *gsp )
{
    std::lock_guard<std::mutex> lock( mMutex );

    GraphicsPipelineState *ps = mPipelineStatePool->Get();
    static_cast<BgfxGraphicsPipelineState *>( ps )->Init( desc, gsp );

    return ps;
}

const EDK::Graphics::GraphicsShaderProgram *EDK::Graphics::BgfxManager::CreateShaderProgram( const VertexShaderBlob *vs,
                                                                                             const PixelShaderBlob *ps )
{
    std::lock_guard<std::mutex> lock( mMutex );

    ShaderProgram *program = nullptr;

    if ( vs && ps )
    {
        const BgfxShaderBlob *vs_blob = static_cast<const BgfxShaderBlob *>( vs );
        const BgfxShaderBlob *ps_blob = static_cast<const BgfxShaderBlob *>( ps );

        bgfx::ProgramHandle handle = bgfx::createProgram( vs_blob->GetShaderHandle(), ps_blob->GetShaderHandle() );

        program = mShaderProgramPool->Get();
        static_cast<BgfxShaderProgram *>( program )->Init( handle );
    }

    return program;
}


EDK::Graphics::GraphicsCommandList *EDK::Graphics::BgfxManager::CreateGraphicsCommandList()
{
    std::lock_guard<std::mutex> lock( mMutex );

    return mGraphicsCommandListPool->Get();
}

const EDK::Graphics::SwapChain *EDK::Graphics::BgfxManager::GetMainWindow()
{
    return mMainwindow;
}

bgfx::VertexDecl EDK::Graphics::GetBgfxVertexDecl( const BufferLayoutDecl &layout )
{
    bgfx::VertexDecl vertexDecl;
    vertexDecl.begin();

    for ( const LayoutItem &item : layout.GetItems() )
    {
        if ( item.itemView == LayoutItemView::Padding )
        {
            vertexDecl.skip( item.data.paddingBytes );
        }
        else if ( item.itemView == LayoutItemView::Attribute )
        {
            if ( item.data.layout.format.formatView != DataFormatView::RGBA )
            {
                Console::Errorf( "Tried to process a bgfx layout item, where the data format is not RGBA" );

                vertexDecl.skip( item.data.layout.format.GetByteSize() );
            }
            else
            {
                const bgfx::Attrib::Enum bgfxAttrib = GetBgfxAttrib( item.data.layout.attribute );
                const bool isNormalized = IsNormalizedAttribType( item.data.layout.format.data.rgbaView.type );
                const bgfx::AttribType::Enum bgfxAttribType = GetBgfxAttribType( item.data.layout.format.data.rgbaView.type );
                const U32 numelements = item.data.layout.format.data.rgbaView.elements;

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

bool EDK::Graphics::IsNormalizedAttribType( const AttributeType type )
{
    switch ( type )
    {
    case AttributeType::UINT_NORM_8:
        return true;

    case AttributeType::UINT_NORM_16:
        return true;

    case AttributeType::SINT_NORM_8:
        return true;

    case AttributeType::SINT_NORM_16:
        return true;

    case AttributeType::UINT_NORM_SRGB_8:
        return true;

    default:
        return false;
    }
}

bgfx::AttribType::Enum EDK::Graphics::GetBgfxAttribType( const AttributeType type )
{
    switch ( type )
    {
    case AttributeType::UINT_8:
        return bgfx::AttribType::Enum::Uint8;

    case AttributeType::UINT_NORM_8:
        return bgfx::AttribType::Enum::Uint8;

    case AttributeType::SINT_16:
        return bgfx::AttribType::Enum::Int16;

    case AttributeType::SINT_NORM_16:
        return bgfx::AttribType::Enum::Int16;

    case AttributeType::FLOAT_16:
        return bgfx::AttribType::Enum::Half;

    case AttributeType::FLOAT_32:
        return bgfx::AttribType::Enum::Float;

    default:
        Console::Errorf( "Could not translate an engine attribute type to a bgfx attribute type, unsupported attribute." );
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