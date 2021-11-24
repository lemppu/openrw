#include "core.h"
#include "config.h"
#include "argparser.h"

#include <string>
#include <map>
#include <optional>
#include <memory>
#include <variant>

namespace orw::cfg {

static std::vector<ConfigOption> InitOptions(void) {
    return std::vector<ConfigOption>{
        {.name="data_path",.client_name="game",
         .description="Location to game data files",
         .keys=std::vector<std::string>{"data","d"},
         .option_type=OptionType::kCmdLine | OptionType::kIniFile,
         .value_type=ValueType::kString,
         .default_value="$HOME/.local/openrw/data",
         .current_value="$HOME/.local/openrw/data" },
        {.name="conf_path",.client_name="game",
         .description="Location of game configuration file",
         .keys=std::vector<std::string>{"conf","c"},
         .option_type=OptionType::kCmdLine,
         .value_type=ValueType::kString,
         .default_value="$HOME/.comfig/openrw/openrw.ini",
         .current_value="$HOME/.config/openrw/openrw.ini"},
        {.name="no_config",.client_name="game",
         .description="Skip the loading of comfig file",
         .keys=std::vector<std::string>{"noconf","nc"},
         .option_type=OptionType::kCmdLine,
         .value_type=ValueType::kBool,
         .default_value=false,
         .current_value=false}
    };
}

// Free function, make public if needed.
static std::optional<ConfigOption> GetOption(std::vector<ConfigOption> data,
                                             std::string option_name) {

    for (auto it = data.begin(); it != data.end(); ++it) 
        if (it->name == option_name) 
            return {*it};

    return {};

}

static bool NoConfigSet(std::vector<ConfigOption> data) {

    std::optional<ConfigOption> noconf_opt = GetOption(data, "no_config");

    return (noconf_opt.has_value()) 
           ? std::get<bool>(noconf_opt.value().current_value)
           : false;

}

static std::string GetConfPath(std::vector<ConfigOption> data) {
    
    std::optional<ConfigOption> conf_path = GetOption(data, "conf_path");

    return (conf_path.has_value())
           ? std::get<std::string>(conf_path.value().current_value)
           : "";

}

Core::Core(int argc, char **argv) {

    data_ = InitOptions();

    ArgParser args(argc, argv);

    // data_ = MergeOptions(args.GetConfig());

    if (NoConfigSet(data_))
        return;        

    std::string conf_path = GetConfPath(data_);
    
    if (conf_path.empty())
        return;

    // IniParser ini(conf_path);

    // data_ = MergeConfig(ini,data_);
    // data_ = MergeConfig(args,data_);
}

std::optional<ConfigVariant> Core::GetValue(std::string key) {

    for (auto it = data_.begin(); it != data_.end(); ++it) 
        if (it->name == key)
            return {it->current_value};
    
    return {};

}


Result Core::SetValue(std::string name, ConfigVariant value) {

    std::optional<ConfigOption> option = GetOption(data_, name);

    if (option.has_value() == false)
        return Result::kNoSuchOption;

    if (VerifyValueType(value, option.value().value_type) == false)
        return Result::kInvalidValueType;
        
    option.value().current_value = value;

    return Result::kOk;

}

} // namespace orw::cfg
