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
         .current_value="$HOME/.config/openrw/openrw.ini"}
    };
}
// TODO: It should be guaranteed that default has the value of game.path,
// but if for some reason it does not happen, even though it is set in 
// InsertDefaults(), maybe we should throw runtime exception, or that would
// just be some extra clutter? 
static std::string GetConfPath(std::optional<ConfigVariant> arg_path,
                              std::vector<ConfigOption> data) {

    if (arg_path.has_value())
        for (auto it = data.begin(); it != data.end(); ++it)
            if (it->name == "config_path")
                it->current_value = arg_path.value();
   
    return "";
}

Core::Core(int argc, char **argv) {

    this->InsertDefaults();

    ArgParser args(argc, argv);

    std::string conf_path = GetConfPath(args.GetValue("conf_path"), data_);
    
    // IniParser ini(conf_path);

    // data_ = MergeConfig(ini,data_);
    // data_ = MergeConfig(args,data_);
}

void Core::InsertDefaults() {

    /*data_.insert({"game.path",std::string("$HOME/.local/openrw/data")});
    data_.insert({"input.invert_y", false});
    data_.insert({"conf_path", std::string("/tmp/openrw.ini")});*/

}

std::optional<ConfigVariant> Core::GetValue(std::string key) {

    for (ConfigMap::iterator it = data_.begin(); it != data_.end(); ++it) 
        if (it->first == key)
            return {it->second};
    
    return {};

}

Result Core::SetValue(std::string key, ConfigVariant value) {

    ConfigMap::iterator it = data_.find(key);

    if (it != data_.end())
        it->second = value;
    else
        data_.insert({key, value});

    return Result::kOk;

}

} // namespace orw::cfg
