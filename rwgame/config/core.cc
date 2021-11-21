#include "core.h"
#include "config.h"

#include <string>
#include <map>
#include <optional>

namespace orw::cfg {

static void InsertDefaults(std::map<std::string, Value> *data) {
    data->insert({"game.path","$HOME/.local/openrw/data"});
    data->insert({"input.invert_y", false});
}

Core::Core(int argc, char **argv) {
    argv[0]++;
    argc++;
    InsertDefaults(&data_);
}

std::optional<Value> Core::GetValue(std::string key) {

    for (std::map<std::string, Value>::iterator it = data_.begin();
         it != data_.end(); ++it) {
        if (it->first == key)
            return {it->second};
    }

    return {};

}

} // namespace orw::cfg
