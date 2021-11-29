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

TEST(CoreDefaults, FailTest) {
   
}

TEST(CoreDefaults, SetValue) {

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

} // namespace orw
