#include "gfx/bgfx/bgfxIndexBuffer.h"

EDK::Graphics::BgfxIndexBuffer::BgfxIndexBuffer()
{

}

bgfx::IndexBufferHandle EDK::Graphics::BgfxIndexBuffer::GetIndexBufferHandle() const
{
    return mBufferHandle;
}

// Required by the object pool
void EDK::Graphics::BgfxIndexBuffer::OnInit()
{

}
void EDK::Graphics::BgfxIndexBuffer::OnRelease()
{

}


void EDK::Graphics::BgfxIndexBuffer::Init( const IndexBufferDesc &desc, const bgfx::IndexBufferHandle &handle )
{
    mDesc = desc;
    mBufferHandle = handle;
}