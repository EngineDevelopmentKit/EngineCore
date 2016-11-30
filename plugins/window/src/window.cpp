
#include "window/sfmlWindowManager.h"

#include "window/window.h"

#include "api/controller.h"

void WindowPlugin::OnInit()
{
    Controller::Add<EDK::SFMLWindowManager>();
}

SET_PLUGIN( WindowPlugin );