#include "config.h"

#include <CppUTest/TestHarness.h>

#include <string>
#include <variant>

namespace orw {

static cfg::Configurator *config;

static cfg::ConfigOption simpleValidTestOption = {
             .name="test_option",.client_name="test_client",
             .description="Test option",
             .keys=std::vector<std::string>{"-test"},
             .option_type=cfg::type::kAll,
             .value_type=cfg::ValueType::kString,
             .default_value="default value",
             .current_value="rest value"
}; 

cfg::Result TestCallback([[maybe_unused]]cfg::ConfigOption option) {
    return cfg::Result::kOk;
}

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

TEST(ConfigDefaults, RegisterClientSuccess) {
    
    cfg::Result res = config->RegisterClient(
        cfg::ConfigClient{
            .client_name = "test_client", .callback=TestCallback
        },
        std::vector<cfg::ConfigOption>{ simpleValidTestOption }
    );

    CHECK(res == cfg::Result::kOk);
}

IGNORE_TEST(ConfigDefaults, RegisterClientFail) {
}

IGNORE_TEST(ConfigDefaults, DataPathValid) {

    std::optional<cfg::ConfigVariant> dataPath = config->GetValue("game.path");

    CHECK(dataPath.has_value());
    std::string ref_value = std::string("$HOME/.local/openrw/data");
    CHECK(dataPath.value() == cfg::ConfigVariant(ref_value));

}

IGNORE_TEST(ConfigDefaults, ValueReadInvalidType) {

    std::optional<cfg::ConfigVariant> ret = config->GetValue("game.path");
    CHECK(ret.has_value());

    CHECK(std::get_if<int>(&(ret.value())) == nullptr);
    CHECK(ret.value() != cfg::ConfigVariant(1));

}

IGNORE_TEST(ConfigDefaults, GetValueInvalidKey) {

    std::optional<cfg::ConfigVariant> ret = config->GetValue("key_not_exist");

    CHECK(ret.has_value() == false);

}

IGNORE_TEST(ConfigDefaults, InvertMouseValid) {
    
    std::optional<cfg::ConfigVariant> option = config->GetValue("input.invert_y");

    CHECK(option.has_value());
    CHECK(option.value() == cfg::ConfigVariant(false));
    
}

IGNORE_TEST(ConfigDefaults, SetValue) {

    cfg::Result res = config->SetValue("testkey", 123);

    CHECK(res == cfg::Result::kOk);
    CHECK(config->GetValue("testkey") == cfg::ConfigVariant(123));

    res = config->SetValue("testkey", 456);

    CHECK(res == cfg::Result::kOk);
    CHECK(config->GetValue("testkey") == cfg::ConfigVariant(456));

}

} // namespace orw
