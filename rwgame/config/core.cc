#include "core.h"
#include "config.h"
#include "argparser.h"

#include <string>
#include <map>
#include <optional>
#include <memory>
#include <variant>

namespace orw::cfg {

// TODO: It should be guaranteed that default has the value of game.path,
// but if for some reason it does not happen, even though it is set in 
// InsertDefaults(), maybe we should throw runtime exception, or that would
// just be some extra clutter? 
static std::string GetConfPath(std::optional<ConfigValue> arg_path,
                               ConfigMap defaults) {

    if (arg_path.has_value())
        return std::get<std::string>(arg_path.value());
    else
        return std::get<std::string>(defaults.find("conf_path")->second);

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

    data_.insert({"game.path",std::string("$HOME/.local/openrw/data")});
    data_.insert({"input.invert_y", false});
    data_.insert({"conf_path", std::string("/tmp/openrw.ini")});

}

std::optional<ConfigValue> Core::GetValue(std::string key) {

    for (ConfigMap::iterator it = data_.begin(); it != data_.end(); ++it) 
        if (it->first == key)
            return {it->second};
    
    return {};

}

Result Core::SetValue(std::string key, ConfigValue value) {

    ConfigMap::iterator it = data_.find(key);

    if (it != data_.end())
        it->second = value;
    else
        data_.insert({key, value});

    return Result::kOk;

}

} // namespace orw::cfg
