#pragma once

#include "dreamcap/ui_root.h"

namespace dc {

class UIRoot;
class Module {
public:
    Module(UIRoot& root)
        : root(root)
    {
    }
    virtual void update() {};

protected:
    UIRoot& root;
};

} // namespace dc