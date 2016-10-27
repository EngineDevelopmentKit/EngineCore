#include "gfx/gfxBufferDecl.h"

#include "common/util.h"

EDK::Graphics::BufferLayoutDecl::LayoutItem::LayoutItem() :
    itemView( LayoutItemView::None )
{

}
EDK::Graphics::BufferLayoutDecl::LayoutItem::LayoutItem( const U32 paddingBytes ) :
    itemView( LayoutItemView::Padding )
{
    data.paddingBytes = paddingBytes;
}

EDK::Graphics::BufferLayoutDecl::LayoutItem::LayoutItem( const ShaderAttribute &attribute,
                                                         const GpuDataFormat &format ) :
    itemView( LayoutItemView::Attribute )
{
    data.attribute = attribute;
    data.format = format;
}

EDK::Graphics::BufferLayoutDecl::BufferLayoutDecl( const U32 alignment ) :
    mStride( 0 ), mAlignment( alignment ), mContentFlags( 0 )
{

}

void EDK::Graphics::BufferLayoutDecl::Add( const ShaderAttribute atribute, const GpuDataFormat &format )
{
    //make sure we start the item at the alginment boundary
    const U32 remainder = mStride % mAlignment;

    // Pad
    Pad( remainder );

    // Add item
    mContent.push_back( LayoutItem( atribute, format ) );

    mStride += format.GetByteSize();
}

void EDK::Graphics::BufferLayoutDecl::Pad( const U32 bytes )
{
    // Add item
    mContent.push_back( LayoutItem( bytes ) );

    // add bytes
    mStride += bytes;
}

const std::vector< EDK::Graphics::BufferLayoutDecl::LayoutItem > &EDK::Graphics::BufferLayoutDecl::GetItems() const
{
    return mContent;
}