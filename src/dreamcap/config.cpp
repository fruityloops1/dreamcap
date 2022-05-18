#include "dreamcap/config.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#define string(x) #x
#define cget(NAME) NAME = config[string(NAME)];

bool dc::Config::load(const std::string& filename)
{
    nlohmann::json config;
    std::ifstream s(filename);
    s >> config;
    s.close();
    try {
        cget(extractedFMapPath);
        cget(uiSize);
    } catch (nlohmann::detail::type_error& e) {
        defaultv();
    }
    if (!std::filesystem::exists(extractedFMapPath))
        throw std::invalid_argument("FMap path does not exist");
    return true;
}

#define cset(NAME) config[string(NAME)] = NAME

void dc::Config::save(const std::string& filename)
{
    std::ofstream ini(filename);
    nlohmann::json config;
    cset(extractedFMapPath);
    cset(uiSize);
    ini << config;
    ini.close();
}

void dc::Config::defaultv()
{
    extractedFMapPath = ".";
    uiSize = 16;
}