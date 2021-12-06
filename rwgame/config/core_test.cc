#include "core.h"

#include <CppUTest/TestHarness.h>

namespace orw {

static cfg::Core *core;

TEST_GROUP(CoreDefaults) {

    void setup() {
        int argc = 1;
        char *argv[] = { (char*)"testrunner" };

        core = new cfg::Core(argc,argv);
    }

    void teardown() {
        delete core;
    }

};

TEST_GROUP(CoreNoConfig) {
    
    void setup() {
        int argc = 2;
        char *argv[] = { (char*)"testrunner", (char*)"-noconf" };

        core = new cfg::Core(argc,argv);
    }

    void teardown() {
        delete core;
    }
};

TEST_GROUP(CoreEmptyConfig) {
    void setup() {
        int argc = 3;
        char *argv[] = { (char*)"testrunner", (char*)"-conf", (char*)" " };

        core = new cfg::Core(argc, argv);
    }

    void teardown() {
        delete core;
    }
};

TEST(CoreDefaults, SetValueSuccess) {

    std::string path1 = "/usr/share/games/openrw/data";
    std::string path2 = "/opt/openrw/data";

    cfg::Result res = core->SetValue(
        "game", "data_path", path1);

    CHECK(res == cfg::Result::kOk);
    CHECK(core->GetValue("game","data_path") == cfg::ConfigVariant(path1));

    res = core->SetValue("game", "data_path", path2);

    CHECK(res == cfg::Result::kOk);
    CHECK(core->GetValue("game","data_path") == cfg::ConfigVariant(path2));

}

TEST(CoreNoConfig, Default) {
    CHECK(core->GetValue("game", "no_config") == cfg::ConfigVariant(true));
}

TEST(CoreDefaults, SetValueFail) {
    cfg::Result res = core->SetValue("fake_component", "fake_name", false);
    CHECK(res == cfg::Result::kNoSuchOption);
}

TEST(CoreEmptyConfig, ConfEmpty) {
    CHECK(core->GetValue("game", "conf_path") == cfg::ConfigVariant(" "));
}

} // namespace orw
