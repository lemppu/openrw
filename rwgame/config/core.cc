#include "core.h"
#include "config.h"
#include "argparser.h"

#include <string>
#include <map>
#include <optional>
#include <memory>
#include <variant>
#include <vector>

namespace orw::cfg {

static std::vector<ConfigOption> InitOptions(void) {
    return std::vector<ConfigOption>{
        {.name="data_path",.component_name="game",
         .description="Location to game data files",
         .keys=std::vector<std::string>{"data","d"},
         .option_type=type::kCmdLine | type::kIniFile,
         .value_type=ValueType::kString,
         .default_value="$HOME/.local/openrw/data",
         .current_value="$HOME/.local/openrw/data" },
        {.name="conf_path",.component_name="game",
         .description="Location of game configuration file",
         .keys=std::vector<std::string>{"conf","c"},
         .option_type=type::kCmdLine,
         .value_type=ValueType::kString,
         .default_value="$HOME/.comfig/openrw/openrw.ini",
         .current_value="$HOME/.config/openrw/openrw.ini"},
        {.name="no_config",.component_name="game",
         .description="Skip the loading of comfig file",
         .keys=std::vector<std::string>{"noconf","nc"},
         .option_type=type::kCmdLine,
         .value_type=ValueType::kBool,
         .default_value=false,
         .current_value=false},
        {.name="invert_y",.component_name="input",
         .description="Invert mouse y-axis",
         .keys=std::vector<std::string>{"-invert_y","-iy"},
         .option_type=type::kCmdLine | type::kIniFile | type::kUsrMenu,
         .value_type=ValueType::kBool,
         .default_value=false,
         .current_value=false}
    };
}

// Free function, make public if needed.
// Returns a copy of the ConfigOption, so do not try to use to change value
static std::optional<ConfigOption> GetOption(std::vector<ConfigOption> data,
                                             std::string component,
                                             std::string option_name) {

    for (auto it = data.begin(); it != data.end(); ++it) 
        if (it->component_name == component  && it->name == option_name) 
            return {*it};

    return {};

}

static bool NoConfigSet(std::vector<ConfigOption> data) {

    std::optional<ConfigOption> noconf_opt = GetOption(data, "game",
                                                       "no_config");

    return (noconf_opt.has_value()) 
           ? std::get<bool>(noconf_opt.value().current_value)
           : false;

}

static std::string GetConfPath(std::vector<ConfigOption> data) {
    
    std::optional<ConfigOption> conf_path = GetOption(data, "game",
                                                      "conf_path");

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

std::optional<ConfigVariant> Core::GetValue(std::string component,
                                            std::string name) {

    for (auto it = data_.begin(); it != data_.end(); ++it) 
        if (it->component_name == component && it->name == name)
            return {it->current_value};
    
    return {};

}

static bool OptionMatch(ConfigOption option, std::string component, 
                        std::string name) {
    return (option.component_name == component && option.name == name);
}

std::optional<ConfigClient> Core::GetClient(std::string component) {

    for (auto it = clients_.begin(); it != clients_.end(); ++it)
        if (it->client_name == component)
            return {*it};
 
    return {};
}

Result Core::SetValue(std::string component, std::string name,
                      ConfigVariant value) {

    for (auto it = data_.begin(); it != data_.end(); ++it) {

        if (OptionMatch(*it, component, name) == false)
            continue; 
             
        if (VerifyValueType(value, it->value_type) == false)
            return Result::kInvalidValueType;

        it->current_value = value;

        auto client = GetClient(component); 

        if (client.has_value())
            client.value().callback(*it);

        return Result::kOk;
        
    }

    return Result::kNoSuchOption;
}

Result Core::RegisterClient(ConfigClient new_client,
                            [[maybe_unused]]std::vector<ConfigOption> options) {

    for (auto it = clients_.begin(); it != clients_.end(); ++it)
        if (it->client_name == new_client.client_name)
            return Result::kComponentAlreadyRegistered;

    clients_.push_back(new_client);

    std::copy(options.begin(), options.end(), std::back_inserter(data_));

    return Result::kOk;
}

} // namespace orw::cfg
