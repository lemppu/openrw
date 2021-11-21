#ifndef OPENRW_CONFIG_CORE_H_
#define OPENRW_CONFIG_CORE_H_

#include "config.h"

#include <optional>
#include <string>
#include <map>

namespace orw::cfg {

class Core {

public:

    Core(int argc, char **argv);

    std::optional<Value> GetValue(std::string key);

    //Result SetValue(std::string key, Value value);

private:

    std::map<std::string, Value> data_;

};

} // namespace orw::cfg

#endif // OPENRW_CONFIG_CORE_H_
