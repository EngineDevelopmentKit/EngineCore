#include "gfx/bgfx/bgfxRenderTarget.h"

EDK::Graphics::BgfxFrameBuffer::BgfxFrameBuffer()
{

}

bgfx::FrameBufferHandle EDK::Graphics::BgfxFrameBuffer::GetHandle() const
{
    return mHandle;
}

void EDK::Graphics::BgfxFrameBuffer::OnInit()
{

}

void EDK::Graphics::BgfxFrameBuffer::OnRelease()
{

}

void EDK::Graphics::BgfxFrameBuffer::Init( bgfx::FrameBufferHandle handle )
{
    mHandle = handle;
}