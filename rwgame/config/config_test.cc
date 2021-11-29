#include "config.h"

#include <CppUTest/TestHarness.h>

#include <string>
#include <variant>

namespace orw {

static cfg::Configurator *config;

static cfg::ConfigOption simpleValidTestOption = {
             .name="test_option",.component_name="test_component",
             .description="Test option",
             .keys=std::vector<std::string>{"-test"},
             .option_type=cfg::type::kAll,
             .value_type=cfg::ValueType::kString,
             .default_value="default value",
             .current_value="rest value"
}; 

static cfg::ConfigOption simpleValidTestOptionInt = {
             .name="test_int",.component_name="test_component",
             .description="Test integer option",
             .keys=std::vector<std::string>{"-int"},
             .option_type=cfg::type::kCmdLine,
             .value_type=cfg::ValueType::kInt,
             .default_value=123,
             .current_value=123
}; 

static bool callback_called = false;

cfg::Result TestCallback([[maybe_unused]]cfg::ConfigOption option) {

    callback_called = true;

    return cfg::Result::kOk;

}

static cfg::ConfigClient test_client = {
    .client_name = "test_component", .callback=TestCallback
};

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
        test_client,
        std::vector<cfg::ConfigOption>{ simpleValidTestOption }
    );

    CHECK(res == cfg::Result::kOk);
}

TEST(ConfigDefaults, RegisterClientFail) {

    cfg::Result res = config->RegisterClient(
        test_client,
        std::vector<cfg::ConfigOption>{ simpleValidTestOption }
    );

    CHECK(res == cfg::Result::kOk);

    res = config->RegisterClient(
        test_client,
        std::vector<cfg::ConfigOption>{ simpleValidTestOption }
    );

    CHECK(res == cfg::Result::kComponentAlreadyRegistered);
}

TEST(ConfigDefaults, TestCallback) {

    cfg::Result res = config->RegisterClient(
        test_client,
        std::vector<cfg::ConfigOption>{ simpleValidTestOption }
    ); 

    CHECK(res == cfg::Result::kOk);

    callback_called = false;

    config->SetValue("test_component", "test_option", "new value");

    CHECK_TRUE(callback_called);

}

TEST(ConfigDefaults, DataPathValid) {

    std::optional<cfg::ConfigVariant> dataPath;
    dataPath = config->GetValue("game","data_path");

    CHECK(dataPath.has_value());
    std::string ref_value = std::string("$HOME/.local/openrw/data");
    CHECK(dataPath.value() == cfg::ConfigVariant(ref_value));

}

TEST(ConfigDefaults, ValueReadInvalidType) {

    std::optional<cfg::ConfigVariant> ret = config->GetValue("game","data_path");
    CHECK(ret.has_value());

    CHECK(std::get_if<int>(&(ret.value())) == nullptr);
    CHECK(ret.value() != cfg::ConfigVariant(1));

}

TEST(ConfigDefaults, GetValueInvalidKey) {

    std::optional<cfg::ConfigVariant> ret;
    ret = config->GetValue("fake","key");

    CHECK(ret.has_value() == false);

}

TEST(ConfigDefaults, InvertMouseValid) {
    
    std::optional<cfg::ConfigVariant> option;
    option = config->GetValue("input","invert_y");

    CHECK(option.has_value());
    CHECK(option.value() == cfg::ConfigVariant(false));
    
}

TEST(ConfigDefaults, SetValueSuccess) {

    std::string path1 = "/usr/share/games/openrw/openrw.ini";
    std::string path2 = "/etc/openrw/openrw.ini";

    cfg::Result res = config->SetValue(
        "game",
        "data_path", 
        path1
    );

    CHECK(res == cfg::Result::kOk);
    CHECK(config->GetValue("game", "data_path").value() == cfg::ConfigVariant(path1));

    res = config->SetValue("game", "data_path",  path2);

    CHECK(res == cfg::Result::kOk);
    CHECK(config->GetValue("game","data_path") == cfg::ConfigVariant(path2));

}

} // namespace orw
