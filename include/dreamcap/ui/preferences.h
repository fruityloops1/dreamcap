#pragma once

#include "dreamcap/ui_module.h"

namespace dc {
namespace ui {

    class Preferences : public Module {
    public:
        Preferences(UIRoot& parent)
            : Module(parent)
        {
        }
        void update() override;

    private:
        bool mChanged = false;
        bool mRestartRequired = false;
    };

} // namespace ui
} // namespace dc
