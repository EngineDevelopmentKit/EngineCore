#include "gfx/bgfx/bgfxCommandList.h"
#include "gfx/bgfx/bgfxIndexBuffer.h"
#include "gfx/bgfx/bgfxVertexBuffer.h"
#include "gfx/bgfx/bgfxRenderTarget.h"
#include "gfx/bgfx/bgfxPipelineState.h"
#include "gfx/bgfx/bgfxShaderProgram.h"
#include "gfx/bgfx/bgfxEnumTranslate.h"

#include "common/util.h"

#define TEMP_VIEWID 0

EDK::Graphics::BgfxGraphicsCommandList::BgfxGraphicsCommandList() :
    mDrawCalls( 0 ), mActiveProgram( nullptr )
{

}

void EDK::Graphics::BgfxGraphicsCommandList::OnInit()
{

}

void EDK::Graphics::BgfxGraphicsCommandList::OnRelease()
{

}

void EDK::Graphics::BgfxGraphicsCommandList::BeginRecording( const FrameBuffer *rtv, const ViewPort &viewPort,
                                                             const ClearStrategy &cstrat, const Matrix4f &viewm,
                                                             const Matrix4f &projm, const Scissor &scissor )
{
    // Clear state
    bgfx::touch( 0 );

    mDrawCalls = 0;
    mActiveProgram = nullptr;

    const U16 bgfxClearFlags = GetBgfxClearFlags( cstrat.flags );

    bgfx::setViewName( TEMP_VIEWID, mName.c_str() );
    bgfx::setViewClear( TEMP_VIEWID, bgfxClearFlags, cstrat.colour, cstrat.depth, cstrat.stencil );
    bgfx::setViewRect( TEMP_VIEWID, viewPort.x, viewPort.y, viewPort.width, viewPort.height );
    bgfx::setViewTransform( TEMP_VIEWID, viewm.Data(), projm.Data() );

    if ( rtv )
    {
        bgfx::setViewFrameBuffer( TEMP_VIEWID, static_cast<const BgfxFrameBuffer *>( rtv )->GetHandle() );
    }

    if ( scissor.width > 0 && scissor.height > 0 )
    {
        bgfx::setViewScissor( scissor.x, scissor.y, scissor.width, scissor.height );
    }
}

void EDK::Graphics::BgfxGraphicsCommandList::EndRecording()
{

}

void EDK::Graphics::BgfxGraphicsCommandList::Init( const std::string &name )
{
    mName = name;
}

void EDK::Graphics::BgfxGraphicsCommandList::SetVertexBuffer( const VertexBuffer *vb )
{
    bgfx::setVertexBuffer( static_cast<const BgfxVertexBuffer *>( vb )->GetVertexBufferHandle() );
}

void EDK::Graphics::BgfxGraphicsCommandList::SetVertexBufferRange( const VertexBuffer *vb, U32 start, U32 num )
{
    bgfx::setVertexBuffer( static_cast<const BgfxVertexBuffer *>( vb )->GetVertexBufferHandle(), start, num );
}

void EDK::Graphics::BgfxGraphicsCommandList::SetIndexBuffer( const IndexBuffer *ib )
{
    bgfx::setIndexBuffer( static_cast<const BgfxIndexBuffer *>( ib )->GetIndexBufferHandle() );
}

void EDK::Graphics::BgfxGraphicsCommandList::SetIndexBufferRange( const IndexBuffer *ib, U32 start, U32 num )
{
    bgfx::setIndexBuffer( static_cast<const BgfxIndexBuffer *>( ib )->GetIndexBufferHandle(), start, num );
}

void EDK::Graphics::BgfxGraphicsCommandList::SetPipelineState( const GraphicsPipelineState *pso )
{
    const BgfxGraphicsPipelineState *bpso = static_cast<const BgfxGraphicsPipelineState *>( pso );

    mActiveProgram = bpso->GetShaderProgram();

    bgfx::setState( bpso->GetBgfxStateFlags() );
    bgfx::setStencil( bpso->GetBgfxFrontStencilFlags(), bpso->GetBgfxBackStencilFlags() );
}

void EDK::Graphics::BgfxGraphicsCommandList::Submit( const Matrix4f *matrices, U32 numMatrices, U32 sortKey )
{
    // Set model matrix for rendering.
    if ( matrices )
    {
        const U32 matrixCache = bgfx::setTransform( matrices->Data(), numMatrices );

        mDrawCalls += bgfx::submit( TEMP_VIEWID, static_cast<const BgfxShaderProgram *>( mActiveProgram )->GetProgramHandle(),
                                    sortKey, true );
    }
}


