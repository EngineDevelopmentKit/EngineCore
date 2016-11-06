#include "gfx/gfxBufferDecl.h"

#include "common/util.h"

EDK::Graphics::LayoutItem::LayoutItem() :
    itemView( LayoutItemView::UndefinedLayout )
{

}
EDK::Graphics::LayoutItem::LayoutItem( const U32 paddingBytes ) :
    itemView( LayoutItemView::Padding )
{
    data.paddingBytes = paddingBytes;
}

EDK::Graphics::LayoutItem::LayoutItem( const ShaderAttribute &attribute,
                                       const GpuDataFormat &format ) :
    itemView( LayoutItemView::Attribute )
{
    data.layout.attribute = attribute;
    data.layout.format = format;
}

EDK::Graphics::BufferLayoutDecl::BufferLayoutDecl( const U32 alignment ) :
    mStride( 0 ), mAlignment( alignment ), mContentFlags( 0 )
{

}

void EDK::Graphics::BufferLayoutDecl::Add( const ShaderAttribute atribute, const GpuDataFormat &format )
{
    //make sure we start the item at the alginment boundary
    U32 remainder = 0;

    if ( mAlignment > 0 )
    {
        remainder = mStride % mAlignment;
    }

    // Pad
    Pad( remainder );

    // Add item
    mContent.push_back( LayoutItem( atribute, format ) );

    mStride += format.GetByteSize();
}

void EDK::Graphics::BufferLayoutDecl::Pad( const U32 bytes )
{
    if ( bytes > 0 )
    {
        // Add item
        mContent.push_back( LayoutItem( bytes ) );

        // add bytes
        mStride += bytes;
    }
}

U32 EDK::Graphics::BufferLayoutDecl::GetByteSize() const
{
    U32 size = 0;

    for ( auto item : GetItems() )
    {
        if ( item.itemView == LayoutItemView::Attribute )
        {
            size += item.data.layout.format.GetByteSize();
        }
        else if ( item.itemView == LayoutItemView::Padding )
        {
            size += item.data.paddingBytes;
        }
    }

    return size;
}

const std::vector< EDK::Graphics::LayoutItem > &EDK::Graphics::BufferLayoutDecl::GetItems() const
{
    return mContent;
}