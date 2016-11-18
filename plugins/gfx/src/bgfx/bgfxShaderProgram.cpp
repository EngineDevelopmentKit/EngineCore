#include "gfx/bgfx/bgfxShaderProgram.h"

EDK::Graphics::BgfxShaderProgram::BgfxShaderProgram()
{

}

bgfx::ProgramHandle EDK::Graphics::BgfxShaderProgram::GetProgramHandle() const
{
    return mHandle;
}

void EDK::Graphics::BgfxShaderProgram::OnInit()
{

}

void EDK::Graphics::BgfxShaderProgram::OnRelease()
{

}

void EDK::Graphics::BgfxShaderProgram::Init( const bgfx::ProgramHandle &handle )
{
    mHandle = handle;
}
