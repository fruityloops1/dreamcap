#include "dreamcap/common.h"
#include "dreamcap/config.h"
#include "dreamcap/core/fmap.h"
#include "dreamcap/core/graphics/color.h"
#include "dreamcap/core/graphics/sprite.h"
#include "dreamcap/ui_root.h"

#include "nlzss11.h"
#include "span.hpp"
#include <bitset>
#include <filesystem>
#include <fstream>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_raylib.h>
#include <nfd.hpp>
#include <raylib.h>
#include <vector>

void run(dc::Config& config)
{
    SetTraceLogLevel(25);

    InitWindow(dc::common::defaultWindowWidth, dc::common::defaultWindowHeight, "Dreamcap");
    SetTargetFPS(dc::common::defaultFPSCap);
    SetExitKey(KEY_NULL);

    ImGui::CreateContext();
    if (std::filesystem::exists(dc::common::uiFont))
        ImGui::GetIO().Fonts->AddFontFromFileTTF(dc::common::uiFont, config.uiSize, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplRaylib_Init();

    dc::UIRoot root(config);

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

std::vector<uint8_t> readFile(const char* filename)
{
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> fileData(fileSize);
    file.read((char*)&fileData[0], fileSize);
    return fileData;
}

int main()
{
    dc::Config c;
    if (!c.load(dc::common::configPath)) {
        c.defaultv();
        c.save(dc::common::configPath);
    }
    NFD_Init();
    run(c);
    /*dc::FMapDataFileTable table;
    table.load("code.bin");

    dc::FMapDataArchive archive;
    archive.fromFile("FMapDat.dat", table);

    std::ofstream o("FMapDat2.dat", std::ios::binary);
    o.unsetf(std::ios::skipws);
    std::vector<uint8_t> data = archive.toBinary(&table);
    o.write((const char*)data.data(), data.size());

    std::ofstream oo("code.ips", std::ios::binary);
    oo.unsetf(std::ios::skipws);
    std::vector<uint8_t> ips = table.toIPS(dc::regionOffsets.at(0x2124).first, dc::regionOffsets.at(0x2124).second);
    oo.write((const char*)ips.data(), ips.size());*/
    /*std::vector<uint8_t> data = readFile("DObjChr.dat");
    std::vector<uint8_t> dota { data.begin() + 0x4A2D8, data.end() };
    std::vector<uint8_t> decompressed = nlzss11::Decompress(dota);
    std::vector<dc::graphics::cRGBA8888> rgbaData;
    dc::graphics::SpriteRGBA5551 sprite(decompressed, 64, 465);

    rgbaData.resize(sprite.width * sprite.height * sizeof(dc::graphics::cRGBA8888));

    for (int pos = 0; pos < decompressed.size(); pos++) {
        int x = (((pos >> 6) % 8) << 3) | ((pos >> 2) & 0x4) | ((pos >> 1) & 0x2) | (pos & 0x1);
        int y = (((pos >> 6) / 8) << 3) | ((pos >> 3) & 0x4) | ((pos >> 2) & 0x2) | ((pos >> 1) & 0x1);
        uint16_t col = *(uint16_t*)&decompressed[pos * 2];
        dc::graphics::cRGBA5551 colf = *(dc::graphics::cRGBA5551*)&decompressed[pos * 2];
        *(uint32_t*)&rgbaData[(y * (8 * 8)) + x] = 0xFF000000 | ((col & 0b0000001111100000) << 6) | ((col >> 7) & 0b0000000011111000) | ((col & 0b0000000000011111) << 0x13);
        static bool a = false;
        if (!a) {
            a = true;
            printf("col %u\n", col);
            printf("rgbaData[0] %u\n", *(uint32_t*)&rgbaData[0]);
            printf("rgbaData %d %d %d %d\n", rgbaData[0].r, rgbaData[0].g, rgbaData[0].b, rgbaData[0].a);
            // printf("%d %d %d %d\n", colf.r * 8, colf.g * 8, colf.b * 8, colf.a * 255);
            printf("colf ra %d %d\n", colf.r * 8, colf.a * 255);
            // printf("colf gba %d %d %d\n", colf.g * 8, colf.b * 8, colf.a * 255);

            for (int i = 0; i < 16; i++) {
                printf("%c", ((*(uint16_t*)&decompressed[pos * 2]) & (1 << i)) ? '1' : '0');
            }
            printf("\n");
            // printf("%d\n", sprite(x, y).b * 8);
        }
        rgbaData[(y * (8 * 8)) + x].r = ((col >> 7) & 0xF8);
        rgbaData[(y * (8 * 8)) + x].a = 255;
    }

    {
        std::ofstream a("out.bin", std::ios::binary);
        a.unsetf(std::ios::skipws);
        a.write((const char*)decompressed.data(), decompressed.size());
    }

    {
        std::ofstream a("out.raw", std::ios::binary);
        a.unsetf(std::ios::skipws);
        a.write((const char*)rgbaData.data(), rgbaData.size() * sizeof(dc::graphics::cRGBA8888));
    }

    {
        std::vector<uint16_t> testData;
        testData.push_back(0);
        uint16_t f = 0;
        f |= 1UL << 15;
        std::bitset<16> k(f);
        bool g = k[15];
        printf("%d\n", g);
        testData.push_back(f);
        std::ofstream a("test.dat", std::ios::binary);
        a.unsetf(std::ios::skipws);
        a.write((const char*)testData.data(), testData.size() * sizeof(uint16_t));
    }*/

    /*std::vector<uint8_t> data = readFile("BAI_atk_etc.dat");
    for (int i = 0; i < data.size(); i++)
        if (data[i] == 0x11 && *(uint16_t*)&data[i + 5] == 0x000D) {
            std::vector<uint8_t> decompressed = nlzss11::Decompress(std::vector<uint8_t>(data.begin() + i, data.end()));
            {
                std::string name = "asdasd/";
                name.append(std::to_string(i));
                std::ofstream a(name, std::ios::binary);
                a.unsetf(std::ios::skipws);
                a.write((const char*)decompressed.data(), decompressed.size());
            }
        }*/
}
