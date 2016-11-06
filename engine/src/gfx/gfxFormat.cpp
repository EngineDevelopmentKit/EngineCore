#include "gfx/gfxFormat.h"

EDK::Graphics::RGBAView::RGBAView() :
    elements( 0 ), type( AttributeType::Dummy )
{

}

EDK::Graphics::RGBAView::RGBAView( const U32 n_elem, const AttributeType type ) :
    elements( n_elem ), type( type )
{

}

EDK::Graphics::GpuDataFormat::GpuDataFormat() :
    formatView( DataFormatView::UndefView )
{

}

EDK::Graphics::GpuDataFormat::GpuDataFormat( const RGBAView &view ) :
    formatView( DataFormatView::RGBA )
{
    data.rgbaView = view;
}

EDK::Graphics::GpuDataFormat::GpuDataFormat( const SpecialDataFormat &view ) :
    formatView( DataFormatView::Special )
{
    data.specialFormat = view;
}

EDK::Graphics::GpuDataFormat::GpuDataFormat( const CompressedDataFormat &view ) :
    formatView( DataFormatView::Compressed )
{
    data.compressedFormat = view;
}

U32 EDK::Graphics::GpuDataFormat::GetByteSize() const
{
    // Depends on the format!
    U32 bytesize = 0;

    if ( formatView == DataFormatView::Compressed )
    {
        switch ( data.compressedFormat )
        {
        // TODO
        case CompressedDataFormat::Format_BC1_UNORM:
        case CompressedDataFormat::Format_BC1_UNORM_SRGB:
        case CompressedDataFormat::Format_BC2_UNORM:
        case CompressedDataFormat::Format_BC2_UNORM_SRGB:
        case CompressedDataFormat::Format_BC3_UNORM:
        case CompressedDataFormat::Format_BC3_UNORM_SRGB:
        case CompressedDataFormat::Format_BC4_UNORM:
        case CompressedDataFormat::Format_BC4_SNORM:
        case CompressedDataFormat::Format_BC5_UNORM:
        case CompressedDataFormat::Format_BC5_SNORM:
        case CompressedDataFormat::Format_BC7_UNORM:
        case CompressedDataFormat::Format_BC7_UNORM_SRGB:
            break;
        }
    }
    else if ( formatView == DataFormatView::Special )
    {
        switch ( data.specialFormat )
        {
        case SpecialDataFormat::R24S8:
            bytesize = 32;
            break;

        case SpecialDataFormat::RGB_10_A_2_UINT:
            bytesize = 32;
            break;

        case SpecialDataFormat::RGB_10_A_2_UINT_NORM:
            bytesize = 32;
            break;
        }
    }
    else if ( formatView == DataFormatView::RGBA )
    {
        U32 sizePerElement = 0;

        switch ( data.rgbaView.type )
        {
        case AttributeType::UINT_8:
            sizePerElement = 1;
            break;

        case AttributeType::SINT_8:
            sizePerElement = 1;
            break;

        case AttributeType::UINT_NORM_8:
            sizePerElement = 1;
            break;

        case AttributeType::SINT_NORM_8:
            sizePerElement = 1;
            break;

        case AttributeType::UINT_NORM_SRGB_8:
            sizePerElement = 1;
            break;

        case AttributeType::UINT_16:
            sizePerElement = 2;
            break;

        case AttributeType::SINT_16:
            sizePerElement = 2;
            break;

        case AttributeType::FLOAT_16:
            sizePerElement = 2;
            break;

        case AttributeType::UINT_NORM_16:
            sizePerElement = 2;
            break;

        case AttributeType::SINT_NORM_16:
            sizePerElement = 2;
            break;

        case AttributeType::UINT_32:
            sizePerElement = 4;
            break;

        case AttributeType::SINT_32:
            sizePerElement = 4;
            break;

        case AttributeType::FLOAT_32:

            sizePerElement = 4;
            break;
        }

        bytesize = data.rgbaView.elements * sizePerElement;
    }

    return bytesize;
}