#include "config.h"
#include "core.h"

#include <string>
#include <optional>
#include <variant>

namespace orw {

Configurator::Configurator(int argc, char **argv) {
    core_ = std::unique_ptr<cfg::Core>(new cfg::Core(argc,argv));

    config_.data_path = std::string("$HOME/.local/openrw/data");
    config_.invert_y = false;
}

std::optional<cfg::Value> Configurator::GetValue(std::string key) {

    if (key == std::string("game.path"))
        return {cfg::Value(config_.data_path)};
    else if (key == std::string("input.invert_y"))
        return {cfg::Value(config_.invert_y)};

    return {};
}

} // namespace orw
