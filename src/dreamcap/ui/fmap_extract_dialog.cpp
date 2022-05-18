#include "dreamcap/ui/fmap_extract_dialog.h"
#include "dreamcap/ui_module.h"
#include "dreamcap/util.h"
#include "imgui.h"
#include "nfd.h"
#include "nfd.hpp"
#include <cstring>
#include <filesystem>

void dc::ui::FMapExtractDialog::update()
{
    if (root.isMessage("openFMapDialog"))
        ImGui::OpenPopup("Extract FMap files");
    if (ImGui::BeginPopupModal("Extract FMap files")) {

        ImGui::InputText("romfs:/FMap/FMapDat.dat", mCurFMapDatPath, sizeof(mCurFMapDatPath));
        ImGui::SameLine();
        ImGui::PushID("mapbrowse");
        if (ImGui::Button("Browse")) {
            nfdfilteritem_t filter = { "FMapDat.dat", "dat" };
            std::string path = dc::fileDialog(&filter, 1, ".");
            if (path.length() < sizeof(mCurFMapDatPath))
                strcpy(mCurFMapDatPath, path.data());
        }
        ImGui::PopID();
        ImGui::InputText("exefs:/code.bin", mCurCodePath, sizeof(mCurCodePath));
        ImGui::SameLine();
        ImGui::PushID("codebrowse");
        if (ImGui::Button("Browse")) {
            nfdfilteritem_t filter = { "code.bin", "bin" };
            std::string path = dc::fileDialog(&filter, 1, ".");
            if (path.length() < sizeof(mCurCodePath))
                strcpy(mCurCodePath, path.data());
        }
        ImGui::PopID();

        if (std::filesystem::exists(mCurCodePath) && std::filesystem::exists(mCurFMapDatPath)) {
            if (ImGui::Button("OK")) {
            }
            ImGui::SameLine();
        }
        if (ImGui::Button("Cancel"))
            ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }
}