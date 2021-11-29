#include "config.h"
#include "core.h"

#include <string>
#include <optional>
#include <variant>
#include <memory>

namespace orw::cfg {

bool VerifyValueType([[maybe_unused]]ConfigVariant variant, [[maybe_unused]]ValueType type) {
    return true;
}

Configurator::Configurator(int argc, char **argv) {
    core_ = std::unique_ptr<Core>(new Core(argc,argv));
}

Configurator::~Configurator() {
    // Nothing to do here, we just need this because a member is unique_ptr
    // and starts complaining if the destructor is missing.
}

std::optional<ConfigVariant> Configurator::GetValue(std::string component,
                                                    std::string name) {

    return core_->GetValue(component, name);
}

Result Configurator::SetValue(std::string component,
                              std::string name,
                              ConfigVariant value) {

    return core_->SetValue(component, name, value);

}

Result Configurator::RegisterClient(ConfigClient client,
                                    std::vector<ConfigOption> options) {
    return core_->RegisterClient(client, options);
}

} // namespace orw
