#include "gfx/abstract/gfxIndexBuffer.h"

EDK::Graphics::IndexBufferDesc::IndexBufferDesc() :
    flags( 0 )
{

}

EDK::Graphics::IndexBufferDesc::IndexBufferDesc( AttributeType type, U32 flags ) :
    flags( flags ), type( type )
{

}