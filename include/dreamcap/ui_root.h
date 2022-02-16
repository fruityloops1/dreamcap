#pragma once

#include "dreamcap/ui_module.h"
#include <vector>

namespace dc {

class Module;
class UIRoot {
public:
    UIRoot();
    ~UIRoot();
    void update();
    void tryExit();
    inline bool isRunning() { return mIsRunning; }

private:
    bool mIsRunning = true;
    std::vector<Module*> mModules;
};

} // namespace