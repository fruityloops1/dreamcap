#pragma once

#include "dreamcap/ui/window.h"
#include "imgui.h"

void dc::ui::Window::update()
{
    ImGui::Begin("Window");
    ImGui::Text("Hi");
    ImGui::End();
}