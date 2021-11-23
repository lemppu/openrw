#ifndef OPENRW_CONFIG_CORE_H_
#define OPENRW_CONFIG_CORE_H_

#include "config.h"

#include <optional>
#include <string>
#include <map>
#include <vector>

namespace orw::cfg {

using ConfigMap = std::map<std::string, ConfigValue>;

// This is here just temporarily to make previous functionality to work fast.
//
// TODO: Make a struct for config value that contains keys, type and 
// description.
static const std::vector<std::pair<std::string, OptionType>> kValidOptions = {
    {"gamedata", OptionType::kCmdLine | OptionType::kIniFile},
    {"invert_y", OptionType::kAll },
    {"width", OptionType::kCmdLine | OptionType::kIniFile },
    {"w", OptionType::kCmdLine | OptionType::kIniFile },
    {"height", OptionType::kCmdLine | OptionType::kIniFile },
    {"h", OptionType::kCmdLine | OptionType::kIniFile },
    {"fullscreen", OptionType::kCmdLine | OptionType::kIniFile | 
                   OptionType::kBoolean },
    {"f", OptionType::kCmdLine | OptionType::kIniFile | OptionType::kBoolean },
    {"hud_scale", OptionType::kCmdLine | OptionType::kIniFile },
    {"language", OptionType::kCmdLine | OptionType::kIniFile },
    {"config", OptionType::kCmdLine },
    {"c", OptionType::kCmdLine },
    {"noconfig", OptionType::kCmdLine | OptionType::kBoolean },
    {"test", OptionType::kCmdLine },
    {"t", OptionType::kCmdLine },
    {"benchmark", OptionType::kCmdLine },
    {"b", OptionType:: kCmdLine },
    {"newgame", OptionType::kCmdLine | OptionType::kBoolean },
    {"n", OptionType::kCmdLine | OptionType::kBoolean },
    {"load", OptionType::kCmdLine },
    {"l", OptionType::kCmdLine },
    {"help", OptionType::kCmdLine | OptionType::kBoolean }
};

class Core {

public:
    Core(int argc, char **argv);

    std::optional<ConfigValue> GetValue(std::string key);

    Result SetValue(std::string key, ConfigValue value);

private:
    void InsertDefaults();
    ConfigMap data_;

};

} // namespace orw::cfg

#endif // OPENRW_CONFIG_CORE_H_
