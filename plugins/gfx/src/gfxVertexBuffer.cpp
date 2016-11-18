#include "gfx/abstract/gfxVertexBuffer.h"

EDK::Graphics::VertexBufferDesc::VertexBufferDesc() :
    flags( 0 )
{

}

EDK::Graphics::VertexBufferDesc::VertexBufferDesc( const BufferLayoutDecl &layout, U32 flags ) :
    flags( flags ), layoutDecl( layout )
{

}