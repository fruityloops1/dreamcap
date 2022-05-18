#pragma once

#include "dreamcap/ui_module.h"

namespace dc {
namespace ui {

    class FMapExtractDialog : public Module {
    public:
        FMapExtractDialog(UIRoot& parent)
            : Module(parent)
        {
        }
        void update() override;

    private:
        bool mIsOpen = false;
        char mCurFMapDatPath[256] { 0 };
        char mCurCodePath[256] { 0 };
    };

} // namespace ui
} // namespace dc
