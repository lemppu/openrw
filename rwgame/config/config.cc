#include "config.h"
#include "core.h"

#include <string>
#include <optional>
#include <variant>
#include <memory>

namespace orw {

Configurator::Configurator(int argc, char **argv) {
    core_ = std::unique_ptr<cfg::Core>(new cfg::Core(argc,argv));
}

Configurator::~Configurator() {
    // Nothing to do here, we just need this because the member is unique_ptr
    // and starts complaining if the destructor is missing.
}

std::optional<cfg::Value> Configurator::GetValue(std::string key) {

    return core_->GetValue(key);
}

} // namespace orw
