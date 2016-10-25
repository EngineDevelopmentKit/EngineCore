#include "gfx/bgfx/bgfxSwapChain.h"

#include "common/util.h"

EDK::Graphics::BgfxSwapChain::BgfxSwapChain() : mFrameBuffer( nullptr )
{

}

void EDK::Graphics::BgfxSwapChain::Present() const
{
    bgfx::frame();
}

EDK::Graphics::SwapChainDesc EDK::Graphics::BgfxSwapChain::QueryDesc() const
{
    return mDesc;
}

const EDK::Graphics::FrameBuffer *EDK::Graphics::BgfxSwapChain::GetFrameBuffer() const
{
    return mFrameBuffer;
}

void EDK::Graphics::BgfxSwapChain::OnInit()
{

}

void EDK::Graphics::BgfxSwapChain::OnRelease()
{

}

void EDK::Graphics::BgfxSwapChain::Init( FrameBuffer *frameBuffer, const SwapChainDesc &desc )
{
    mDesc = desc;
    mFrameBuffer = frameBuffer;
}