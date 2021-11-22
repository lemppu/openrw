#include "argparser.h"

namespace orw::cfg {

ArgParser::ArgParser(int argc, char **argv) {
    argc++;
    argv[0]++;
}

std::optional<ConfigValue> ArgParser::GetValue(std::string key) {

    for (ConfigMap::iterator it = data_.begin(); it != data_.end(); ++it)
        if (it->first == key)
            return {it->second};

    return {};
}

} // namespace orw::cfg
