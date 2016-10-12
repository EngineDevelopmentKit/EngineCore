#include "gfx/bgfx/bgfxSwapChain.h"

#include <bgfx/bgfx.h>

EDK::Graphics::SwapChainDesc EDK::Graphics::BgfxSwapChain::QueryDesc() const
{
    return mDesc;
}

const EDK::Graphics::FrameBuffer *EDK::Graphics::BgfxSwapChain::GetFrameBuffer() const
{
    return mFrameBuffer;
}

void EDK::Graphics::BgfxSwapChain::Release()
{
    SAFE_RELEASE( mFrameBuffer )
}

void EDK::Graphics::BgfxSwapChain::Present()
{
    bgfx::frame();
}

void EDK::Graphics::BgfxSwapChain::Init( FrameBuffer *frameBuffer, SwapChainDesc &desc )
{
    mDesc = desc;
    mFrameBuffer = frameBuffer;
}