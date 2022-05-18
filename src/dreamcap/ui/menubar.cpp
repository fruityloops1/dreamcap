#include "dreamcap/ui/menubar.h"
#include "imgui.h"

void dc::ui::MenuBar::update()
{
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit"))
                root.tryExit();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
            bool& isPreferencesOpen = std::get<bool>(root.state["isPreferencesOpen"]);
            if (ImGui::MenuItem("Preferences", nullptr, isPreferencesOpen))
                isPreferencesOpen = !isPreferencesOpen;
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools")) {
            if (ImGui::MenuItem("Extract FMapDat.dat"))
                root.sendMessage("openFMapDialog");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}