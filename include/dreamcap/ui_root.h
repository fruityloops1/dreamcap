#pragma once

#include "dreamcap/config.h"
#include "dreamcap/ui_module.h"
#include <unordered_map>
#include <variant>
#include <vector>

namespace dc {

class Module;
class UIRoot {
public:
    UIRoot(const dc::Config& config);
    ~UIRoot();
    void update();
    void tryExit();
    inline bool isRunning() { return mIsRunning; }
    inline void sendMessage(const std::string& key)
    {
        mMessages[key] = true;
    }
    inline bool isMessage(const std::string& key)
    {
        bool& val = mMessages[key];
        if (val)
            mMessages.erase(key);
        return val;
    }

    std::unordered_map<std::string, std::variant<bool, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, std::string>> state;
    inline Config& getConfig() { return mConfig; }

private:
    Config mConfig;
    bool mIsRunning = true;
    std::vector<Module*> mModules;
    std::unordered_map<std::string, bool> mMessages;
};

} // namespace