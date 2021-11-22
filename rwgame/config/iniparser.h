#ifndef OPENRW_CONFIG_INIPARSER_H_
#define OPENRW_CONFIG_INIPARSER_H_

#include "config.h"
#include "core.h"

#include <string>

namespace orw::cfg {

class IniParser {

public:
    IniParser(std::string conf_path);

    ConfigMap GetAllValues() { return data_; }

private:
    ConfigMap data_;

};

} // namespace orw::cfg

#endif // OPENRW_CONFIG_INIPARSER_H_
