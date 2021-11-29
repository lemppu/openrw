#ifndef OPENRW_CONFIG_ARGPARSER_H_
#define OPENRW_CONFIG_ARGPARSER_H_

#include "config.h"
#include "core.h"

namespace orw::cfg {

class ArgParser {

public:
    ArgParser(int argc, char **argv);

    std::optional<ConfigVariant> GetValue(std::string key);

    ConfigMap GetAllData();

private:
    ConfigMap data_;

};

} // namespace orw::cfg

#endif // OPENRW_CONFIG_ARGPARSER_H_
