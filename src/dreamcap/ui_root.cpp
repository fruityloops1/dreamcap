#include "dreamcap/ui_root.h"
#include "dreamcap/ui/fmap_extract_dialog.h"
#include "dreamcap/ui/menubar.h"
#include "dreamcap/ui/preferences.h"
#include "dreamcap/ui_module.h"

dc::UIRoot::UIRoot(const dc::Config& config)
{
    mConfig = config;
    mModules.push_back(new dc::ui::MenuBar(*this));
    mModules.push_back(new dc::ui::FMapExtractDialog(*this));
    mModules.push_back(new dc::ui::Preferences(*this));
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