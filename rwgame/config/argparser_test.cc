/*
 * ArgParser is a dummy class. It does not validate content, only the form, so
 * we only test that there are no values if no arguments are given, and that
 * given the valid set of values, they can be found from the ArgParser.
 *
 * Failure conditions will be tested by giving a faulty input and making sure
 * that only those with a valid form will be inserted into parser.
 */

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

TEST_GROUP(ArgParserInvalidInput) {

   void setup() {
        int argc = 8;
        char *argv[] = { 
            (char*)"testrunner",
            (char*)"gamedata", (char*)"/tmp/data",
            (char*)"-invert_y",
            (char*)"-hud_scale", (char*)"2.0",
            (char*)"language", (char*)"american",
        };

        parser = new cfg::ArgParser(argc, argv);
    }

    void teardown() {
        delete parser;
    }

};

//TEST(ArgParserNoValues, CheckNoValues) {
//   CHECK(parser->GetAllData().size() == 0); 
//}

TEST(ArgParserAllValues, CheckAllValues) {
    CHECK(parser->GetValue("w") == cfg::ConfigVariant(900));
}

TEST(ArgParserInvalidInput, CheckAll) {
    std::optional<cfg::ConfigVariant> hud_scale = parser->GetValue("hud_scale");
    CHECK_TRUE(hud_scale.has_value());
    CHECK(hud_scale.value() == cfg::ConfigVariant(2.0f));

    std::optional<cfg::ConfigVariant> gamedata = parser->GetValue("gamedata");
    CHECK_FALSE(gamedata.has_value());
}


} // namespace orw
