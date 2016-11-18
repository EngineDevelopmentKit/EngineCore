#include "gfx/bgfx/bgfxCommandList.h"
#include "gfx/bgfx/bgfxIndexBuffer.h"
#include "gfx/bgfx/bgfxVertexBuffer.h"
#include "gfx/bgfx/bgfxPipelineState.h"
#include "gfx/bgfx/bgfxShaderProgram.h"
#include "gfx/bgfx/bgfxEnumTranslate.h"

#include "common/util.h"

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

void EDK::Graphics::BgfxGraphicsCommandList::BeginRecording()
{
    // Clear state
    mDrawCalls = 0;
    mActiveProgram = nullptr;

    bgfx::touch( 0 );
}

void EDK::Graphics::BgfxGraphicsCommandList::EndRecording()
{

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

void EDK::Graphics::BgfxGraphicsCommandList::Submit( U32 sortKey )
{
    mDrawCalls += bgfx::submit( 0, static_cast<const BgfxShaderProgram *>( mActiveProgram )->GetProgramHandle(),
                                sortKey, true );
}


