#include "core.h"
#include "config.h"

#include <string>
#include <map>
#include <optional>
#include <memory>

namespace orw::cfg {

static void InsertDefaults(DataMap *data) {
    data->insert({"game.path","$HOME/.local/openrw/data"});
    data->insert({"input.invert_y", false});
}

Core::Core(int argc, char **argv) {
    // Just do something with these before iplementing argument parser that
    // will use them.
    argv[0]++; 
    argc++;
    // ----

    InsertDefaults(&data_);
}

std::optional<ConfigValue> Core::GetValue(std::string key) {

    for (std::map<std::string, ConfigValue>::iterator it = data_.begin();
         it != data_.end(); ++it) {
        if (it->first == key)
            return {it->second};
    }

    return {};

}

} // namespace orw::cfg
