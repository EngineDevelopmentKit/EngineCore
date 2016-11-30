#include "gfx/bgfx/bgfxShaderBlob.h"

EDK::Graphics::BgfxShaderBlob::BgfxShaderBlob()
{

}

void EDK::Graphics::BgfxShaderBlob::OnInit()
{

}

void EDK::Graphics::BgfxShaderBlob::OnRelease()
{

}

void EDK::Graphics::BgfxShaderBlob::Init( const ShaderReflection &desc, const bgfx::ShaderHandle &handle )
{
    mDesc = desc;
    mHandle = handle;
}

bgfx::ShaderHandle EDK::Graphics::BgfxShaderBlob::GetShaderHandle() const
{
    return mHandle;
}