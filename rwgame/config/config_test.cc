#include "config.h"

#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

#include <string>
#include <variant>

namespace orw {

static Configurator *config;

TEST_GROUP(ConfigDefaults) {

    cfg::GameConfig defaults = {
        std::string("$HOME/.local/openrw/data"),
        false,
        800,
        600,
        false,
        1.f,
        std::string("american")
    };

    void setup() {
        int argc = 1;
        char *argv[] = { (char*)"config_test" };

        config = new Configurator(argc, argv);
    }

    void teardown() {
        delete config;
    }
};

TEST(ConfigDefaults, DataPathValid) {

    std::optional<cfg::Value> dataPath = config->GetValue("game.path");

    CHECK(dataPath.has_value());
    CHECK(dataPath.value() == cfg::Value(defaults.data_path));

}

TEST(ConfigDefaults, ValueReadInvalidType) {

    std::optional<cfg::Value> ret = config->GetValue("game.path");
    CHECK(ret.has_value());

    CHECK(std::get_if<int>(&(ret.value())) == nullptr);
    CHECK(ret.value() != cfg::Value(1));

}

TEST(ConfigDefaults, GetValueInvalidKey) {

    std::optional<cfg::Value> ret = config->GetValue("key_not_exist");

    CHECK(ret.has_value() == false);

}

TEST(ConfigDefaults, InvertMouseValid) {
    
    std::optional<cfg::Value> option = config->GetValue("input.invert_y");

    CHECK(option.has_value());
    CHECK(option.value() == cfg::Value(defaults.invert_y));
    
}

} // namespace orw

int main(int argc, char **argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
