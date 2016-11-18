#pragma once
#include "api/controller.h"

#include "plugin/plugin.h"

class ECSPlugin
    : public PluginBase
{
public:

    virtual void OnInit() override
    {
        mNumber = 30;
    }

    U32 GetNumber()
    {
        return mNumber;
    }

private:

    U32 mNumber = 8;
};

namespace ECS
{
    EXPOSE_CONTROLLER_API( ECSPlugin, GetNumber );
}

DEFINE_PLUGIN( ECSPlugin );