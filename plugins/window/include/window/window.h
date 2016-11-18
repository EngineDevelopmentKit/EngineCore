#pragma once
#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "plugin/plugin.h"

class WindowPlugin
    : public PluginBase
{
    void OnInit() override;
};


DEFINE_PLUGIN( WindowPlugin );

#endif