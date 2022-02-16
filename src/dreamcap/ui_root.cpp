#pragma once

#include "dreamcap/ui_root.h"
#include "dreamcap/ui/window.h"
#include "dreamcap/ui_module.h"

dc::UIRoot::UIRoot()
{
    mModules.push_back(new dc::ui::Window(*this));
}

dc::UIRoot::~UIRoot()
{
    for (Module* m : mModules)
        delete m;
}

void dc::UIRoot::update()
{
    for (Module* m : mModules)
        m->update();
}

void dc::UIRoot::tryExit()
{
    mIsRunning = false;
}