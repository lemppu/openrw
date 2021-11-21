#include "config.h"

#include <CppUTest/TestHarness.h>

#include <string>
#include <variant>

namespace orw {

static cfg::Configurator *config;

TEST_GROUP(ConfigDefaults) {

    void setup() {
        int argc = 1;
        char *argv[] = { (char*)"config_test" };

        config = new cfg::Configurator(argc, argv);
    }

    void teardown() {
        delete config;
    }
};

TEST(ConfigDefaults, DataPathValid) {

    std::optional<cfg::ConfigValue> dataPath = config->GetValue("game.path");

    CHECK(dataPath.has_value());
    CHECK(dataPath.value() == cfg::ConfigValue("$HOME/.local/openrw/data"));

}

TEST(ConfigDefaults, ValueReadInvalidType) {

    std::optional<cfg::ConfigValue> ret = config->GetValue("game.path");
    CHECK(ret.has_value());

    CHECK(std::get_if<int>(&(ret.value())) == nullptr);
    CHECK(ret.value() != cfg::ConfigValue(1));

}

TEST(ConfigDefaults, GetValueInvalidKey) {

    std::optional<cfg::ConfigValue> ret = config->GetValue("key_not_exist");

    CHECK(ret.has_value() == false);

}

TEST(ConfigDefaults, InvertMouseValid) {
    
    std::optional<cfg::ConfigValue> option = config->GetValue("input.invert_y");

    CHECK(option.has_value());
    CHECK(option.value() == cfg::ConfigValue(false));
    
}

} // namespace orw
