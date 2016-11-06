#include "gfx/bgfx/bgfxCommandList.h"
#include "gfx/bgfx/bgfxIndexBuffer.h"
#include "gfx/bgfx/bgfxVertexBuffer.h"


EDK::Graphics::BgfxGraphicsCommandList::BgfxGraphicsCommandList()
{
}

void EDK::Graphics::BgfxGraphicsCommandList::OnInit()
{

}

void EDK::Graphics::BgfxGraphicsCommandList::OnRelease()
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