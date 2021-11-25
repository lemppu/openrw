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

IGNORE_TEST(CoreDefaults, SetValue) {

    cfg::Result res = core->SetValue("testkey", 123);

    CHECK(res == cfg::Result::kOk);
    CHECK(core->GetValue("testkey") == cfg::ConfigVariant(123));

    res = core->SetValue("testkey", 456);

    CHECK(res == cfg::Result::kOk);
    CHECK(core->GetValue("testkey") == cfg::ConfigVariant(456));

}


} // namespace orw
