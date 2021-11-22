#include "argparser.h"

#include <CppUTest/TestHarness.h>

namespace orw {

static cfg::ArgParser *parser;


TEST_GROUP(ArgParserNoValues) {

    void setup() {
        int argc = 1;
        char *argv[] = { (char*)"testrunner" };

        parser = new cfg::ArgParser(argc, argv);
    }

    void teardown() {
        delete parser;
    }

};

TEST_GROUP(ArgParserAllValues) {

   void setup() {
        int argc = 23;
        char *argv[] = { 
            (char*)"testrunner",
            (char*)"-gamedata", (char*)"/tmp/data",
            (char*)"-invert_y",
            (char*)"-w", (char*)"900",
            (char*)"-h", (char*)"700",
            (char*)"-f",
            (char*)"-hud_scale", (char*)"2.f",
            (char*)"-language", (char*)"american",
            (char*)"-c",(char*)"/tmp/conf.ini",
            (char*)"-noconfig",
            (char*)"-t",
            (char*)"-b",(char*)"/tmp/benchmark",
            (char*)"-n",
            (char*)"-l",(char*)"/tmp/savegame",
            (char*)"-help"         
        };

        parser = new cfg::ArgParser(argc, argv);
    }

    void teardown() {
        delete parser;
    }

};

TEST(ArgParserNoValues, CheckAll) {

}

TEST(ArgParserAllValues, CheckAll) {

}

} // namespace orw
