#include "gfx/bgfx/bgfxVertexBuffer.h"

EDK::Graphics::BgfxVertexBuffer::BgfxVertexBuffer()
{

}

bgfx::VertexBufferHandle EDK::Graphics::BgfxVertexBuffer::GetVertexBufferHandle() const
{
    return mBufferHandle;
}

// Required by the object pool
void EDK::Graphics::BgfxVertexBuffer::OnInit()
{

}
void EDK::Graphics::BgfxVertexBuffer::OnRelease()
{

}


void EDK::Graphics::BgfxVertexBuffer::Init( const VertexBufferDesc &desc, const bgfx::VertexBufferHandle &handle )
{
    mDesc = desc;
    mBufferHandle = handle;
}