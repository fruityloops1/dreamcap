#pragma once

#include "dreamcap/ui_module.h"

namespace dc {
namespace ui {

    class Window : public Module {
    public:
        Window(UIRoot& parent)
            : Module(parent)
        {
        }
        void update() override;
    };

} // namespace ui
} // namespace dc
