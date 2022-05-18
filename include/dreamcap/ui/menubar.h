#pragma once

#include "dreamcap/ui_module.h"

namespace dc {
namespace ui {

    class MenuBar : public Module {
    public:
        MenuBar(UIRoot& parent)
            : Module(parent)
        {
        }
        void update() override;
    };

} // namespace ui
} // namespace dc
