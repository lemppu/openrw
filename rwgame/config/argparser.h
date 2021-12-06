#ifndef OPENRW_CONFIG_ARGPARSER_H_
#define OPENRW_CONFIG_ARGPARSER_H_

#include "config.h"
#include "core.h"

#include <map>

namespace orw::cfg {

class ArgParser {

public:
    ArgParser(int argc, char **argv);

    std::optional<ConfigVariant> GetValue(std::string key);

private:
    std::map<std::string, ConfigVariant> data_;

};

} // namespace orw::cfg

#endif // OPENRW_CONFIG_ARGPARSER_H_
