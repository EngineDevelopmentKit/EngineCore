#pragma once
#ifndef __EDK_GFX_FACTORY_H__
#define __EDK_GFX_FACTORY_H__

#include "events/abstract/IEvent.h"

#include "gfx/gfxArchitecture.h"
#include "gfx/abstract/gfxSwapChain.h"
#include "gfx/abstract/gfxVertexBuffer.h"

#include "manager/abstract/abstractManager.h"

namespace EDK
{
    struct VideoSwitchEvent : public IEvent
    {
        Graphics::VideoCard videocard;
        Graphics::Interface interface;
        Graphics::SwapChainDesc mainwindow;
    };

    namespace Graphics
    {
        class Manager : public AbstractManager
        {
        public:

            virtual ~Manager() {}

            virtual const VertexBuffer *CreateVertexBuffer( const VertexBufferDesc &desc ) = 0;

            virtual const SwapChain *GetMainWindow() = 0;
        };
    }
}

#endif