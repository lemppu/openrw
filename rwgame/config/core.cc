#include "core.h"
#include "config.h"

#include <string>
#include <map>
#include <optional>
#include <memory>

namespace orw::cfg {

Core::Core(int argc, char **argv) {
    // Just do something with these before iplementing argument parser that
    // will use them.
    argv[0]++; 
    argc++;
    // ----

    this->InsertDefaults();
}

void Core::InsertDefaults() {
    data_.insert({"game.path","$HOME/.local/openrw/data"});
    data_.insert({"input.invert_y", false});
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
