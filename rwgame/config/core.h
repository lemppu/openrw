#ifndef OPENRW_CONFIG_CORE_H_
#define OPENRW_CONFIG_CORE_H_

#include "config.h"

#include <optional>
#include <string>
#include <map>
#include <vector>

namespace orw::cfg {

using ConfigMap = std::map<std::string, ConfigVariant>;

class Core {

public:
    Core(int argc, char **argv);

    std::optional<ConfigVariant> GetValue(std::string key);

    Result SetValue(std::string key, ConfigVariant value);

    Result RegisterClient(ConfigClient client, 
                          std::vector<ConfigOption> options);

private:
    std::vector<ConfigOption> data_;
};

} // namespace orw::cfg

#endif // OPENRW_CONFIG_CORE_H_
