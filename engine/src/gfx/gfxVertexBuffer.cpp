#include "gfx/abstract/gfxVertexBuffer.h"

EDK::Graphics::VertexBufferDesc::VertexBufferDesc() :
    flags( 0 ), memory( nullptr ), memSize( 0 )
{

}

EDK::Graphics::VertexBufferDesc::VertexBufferDesc( const BufferLayoutDecl &layout, void *memory, size_t memSize,
                                                   U32 flags ) :
    flags( flags ), memory( memory ), memSize( memSize ), layoutDecl( layout )
{

}