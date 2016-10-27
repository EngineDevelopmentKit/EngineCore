#include "gfx/gfxFormat.h"

U32 EDK::Graphics::GpuDataFormat::GetByteSize() const
{
    // Depends on the format!
    U32 bytesize = 0;

    if ( formatView == DataFormatView::Compressed )
    {
        switch ( format.compressedFormat )
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
        switch ( format.specialFormat )
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

        switch ( format.rgbaView.type )
        {
        case AtributeType::UINT_8:
            sizePerElement = 1;
            break;

        case AtributeType::SINT_8:
            sizePerElement = 1;
            break;

        case AtributeType::UINT_NORM_8:
            sizePerElement = 1;
            break;

        case AtributeType::SINT_NORM_8:
            sizePerElement = 1;
            break;

        case AtributeType::UINT_NORM_SRGB_8:
            sizePerElement = 1;
            break;

        case AtributeType::UINT_16:
            sizePerElement = 2;
            break;

        case AtributeType::SINT_16:
            sizePerElement = 2;
            break;

        case AtributeType::Float_16:
            sizePerElement = 2;
            break;

        case AtributeType::UINT_NORM_16:
            sizePerElement = 2;
            break;

        case AtributeType::SINT_NORM_16:
            sizePerElement = 2;
            break;

        case AtributeType::UINT_32:
            sizePerElement = 4;
            break;

        case AtributeType::SINT_32:
            sizePerElement = 4;
            break;

        case AtributeType::Float_32:

            sizePerElement = 4;
            break;
        }

        bytesize = format.rgbaView.elements * sizePerElement;
    }

    return bytesize;
}