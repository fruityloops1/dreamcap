#include "dreamcap/ui/preferences.h"
#include "dreamcap/common.h"
#include "dreamcap/core/graphics/color.h"
#include "imgui.h"

void dc::ui::Preferences::update()
{
    if (std::get<bool>(root.state["isPreferencesOpen"]) && ImGui::Begin("Preferences")) {
        if (ImGui::SliderInt("UI Size", &root.getConfig().uiSize, 8, 64)) {
            mRestartRequired = true;
            mChanged = true;
        }
        if (mRestartRequired)
            ImGui::TextColored({ 255, 0, 0, 255 }, "Restart for changes to take effect");
        if (mChanged) {
            if (ImGui::Button("Save")) {
                root.getConfig().save(dc::common::configPath);
                mChanged = false;
            }
            ImGui::SameLine();
        }
        if (ImGui::Button("Close"))
            root.state["isPreferencesOpen"] = false;
        ImGui::End();
    }
}