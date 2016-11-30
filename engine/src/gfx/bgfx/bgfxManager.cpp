#include "gfx/bgfx/bgfxManager.h"
#include "gfx/bgfx/bgfxSwapChain.h"
#include "gfx/bgfx/bgfxShaderBlob.h"
#include "gfx/bgfx/bgfxCommandList.h"
#include "gfx/bgfx/bgfxIndexBuffer.h"
#include "gfx/bgfx/bgfxVertexBuffer.h"
#include "gfx/bgfx/bgfxPipelineState.h"
#include "gfx/bgfx/bgfxShaderProgram.h"
#include "gfx/bgfx/bgfxEnumTranslate.h"

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

    U64 bgfxStateFlags = 0;

    bgfxStateFlags |= GetBgfxDepthTest( desc.depthStencilState.depthTestOp );

    if ( desc.depthStencilState.enableDepthWrite )
    {
        bgfxStateFlags |= BGFX_STATE_DEPTH_WRITE;
    }

    if ( desc.rasterizerState.fillMode == FillMode::FillWireFrame )
    {
        bgfx::setDebug( BGFX_DEBUG_WIREFRAME | BGFX_DEBUG_TEXT );
    }

    bgfxStateFlags |= GetBgfxCullMode( desc.rasterizerState.cullMode, desc.rasterizerState.faceMode );
    bgfxStateFlags |= GetBgfxPrimitiveFlags( desc.rasterizerState.inputLayout );

    if ( desc.rasterizerState.msaaSamples > 0 )
    {
        bgfxStateFlags |= BGFX_STATE_MSAA;
    }

    if ( desc.rasterizerState.lineAntiAliasing )
    {
        bgfxStateFlags |= BGFX_STATE_LINEAA;
    }

    // TEMP do write RGBA
    if ( desc.renderTargetState.writeMask == ChannelTarget::ChannelA )
    {
        bgfxStateFlags |= BGFX_STATE_ALPHA_WRITE;
    }
    else if ( desc.renderTargetState.writeMask == ChannelTarget::ChannelRGB )
    {
        bgfxStateFlags |= BGFX_STATE_RGB_WRITE;
    }
    else if ( desc.renderTargetState.writeMask == ChannelTarget::ChannelRGBA )
    {
        bgfxStateFlags |= BGFX_STATE_RGB_WRITE | BGFX_STATE_ALPHA_WRITE;
    }

    if ( IS_SET( desc.renderTargetState.blendStateFlags, BlendStateFlags::EnableAlphaToCoverage ) )
    {
        bgfxStateFlags |= BGFX_STATE_BLEND_ALPHA_TO_COVERAGE;
    }

    bgfxStateFlags |= BGFX_STATE_BLEND_FUNC_SEPARATE( GetBgfxBlendSource( desc.renderTargetState.srcBlendValue ),
                                                      GetBgfxBlendSource( desc.renderTargetState.destBlendValue ),
                                                      GetBgfxBlendSource( desc.renderTargetState.srcBlendAlpha ),
                                                      GetBgfxBlendSource( desc.renderTargetState.destBlendAlpha ) );

    bgfxStateFlags |= BGFX_STATE_BLEND_EQUATION_SEPARATE( GetBgfxBlendFunc( desc.renderTargetState.blendOp ),
                                                          GetBgfxBlendFunc( desc.renderTargetState.alphaBlendOp ) );

    U32 bgfxFrontStencilFlags = 0;
    U32 bgfxBackStencilFlags = 0;

    if ( desc.depthStencilState.enableStencilTest )
    {
        // store in lower half
        bgfxFrontStencilFlags |= GetBgfxStencilFlags( desc.depthStencilState.frontFaceStencilTest );

        // store in upper half
        bgfxBackStencilFlags |= GetBgfxStencilFlags( desc.depthStencilState.backFaceStencilTest );
    }

    GraphicsPipelineState *ps = mPipelineStatePool->Get();
    static_cast<BgfxGraphicsPipelineState *>( ps )->Init( desc, gsp, bgfxStateFlags, bgfxFrontStencilFlags,
                                                          bgfxBackStencilFlags );

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


EDK::Graphics::GraphicsCommandList *EDK::Graphics::BgfxManager::CreateGraphicsCommandList( const std::string &name )
{
    std::lock_guard<std::mutex> lock( mMutex );

    GraphicsCommandList *commandList = mGraphicsCommandListPool->Get();
    static_cast<BgfxGraphicsCommandList *>( commandList )->Init( name );

    return commandList;
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