#include "dreamcap/common.h"
#include "dreamcap/ui_root.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_raylib.h>
#include <raylib.h>

void run()
{
    SetTraceLogLevel(25);

    InitWindow(dc::common::defaultWindowWidth, dc::common::defaultWindowHeight, "Dreamcap");
    SetTargetFPS(dc::common::defaultFPSCap);
    SetExitKey(KEY_NULL);

    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplRaylib_Init();

    dc::UIRoot root;

    while (root.isRunning()) {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplRaylib_NewFrame();
        ImGui::NewFrame();
        ImGui_ImplRaylib_ProcessEvent();

        BeginDrawing();
        ClearBackground(BLACK);

        root.update();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        EndDrawing();
        if (WindowShouldClose())
            root.tryExit();
    }

    CloseWindow();
}

int main()
{
    run();
}