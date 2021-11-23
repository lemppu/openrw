#ifndef OPENRW_CONFIG_ARGPARSER_H_
#define OPENRW_CONFIG_ARGPARSER_H_

#include "config.h"
#include "core.h"

namespace orw::cfg {

class ArgParser {

public:
    ArgParser(int argc, char **argv);

    std::optional<ConfigValue> GetValue(std::string key);

    ConfigMap GetAllValues();

private:
    ConfigMap data_;

};

} // namespace orw::cfg

#endif // OPENRW_CONFIG_ARGPARSER_H_