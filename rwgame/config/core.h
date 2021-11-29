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

    std::optional<ConfigVariant> GetValue(std::string component,
                                          std::string key);

    Result SetValue(std::string component,
                    std::string name, 
                    ConfigVariant value);

    Result RegisterClient(ConfigClient client, 
                          std::vector<ConfigOption> options);

private:
    std::optional<ConfigClient> GetClient(std::string component);

    std::vector<ConfigOption> data_;
    std::vector<ConfigClient> clients_;

};

} // namespace orw::cfg

#endif // OPENRW_CONFIG_CORE_H_
