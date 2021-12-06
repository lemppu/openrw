/*
 * ArgParser is a class that collects command line arguments into an internal
 * vector. 
 *
 * After this, the Core class of the configurator will take the arguments into
 * ConfigOption structs as needed. 
 *
 * This means that the ArgParser does not validate the content of the arguments.
 * 
 * It will only validate the form as such, that the argument will need to
 * start with dash (-), and if it does not contain an argument for the argument
 * the argument type is implicitly considered to be a boolean with a value of
 * true. 
 *
 * The validation of the content should be done by the caller that has the 
 * information about valid arguments and their types. 
 *
 * After all of the components of the program are loaded, the Configurator can
 * check whether there are any unused, that is, invalid arguments and then
 * act accordingly.
 */

#include "argparser.h"
#include "config.h"
#include "core.h"

#include <string>
#include <map>
#include <variant>
#include <limits>
#include <vector>
#include <algorithm>

// We use C libraries for runtime checking the correct type, so that
// we don't need to use exceptions in program flow, because wrong argument
// type is only a case for the warning, not an error per se.
#include <cstdlib>

namespace orw::cfg {

static std::optional<float> StrToFloat(const char *arg) {

    char *end;
    float val = std::strtof(arg, &end);

    if (*end == '\0')
        return {val};

    return {};
}

static std::optional<int> StrToInt(const char *arg) {

    char *end;
    long val_l = std::strtol(arg, &end, 10); 

    if (*end == '\0' && val_l < std::numeric_limits<int>::max())
        return {(int)val_l};

    return {};
}
// The value of the argument can be any in std::variant, so we
// deduct the correct type our of the c-string here.
static ConfigVariant GetConfigVariant(const char* arg) {

    std::optional<int> val_i = StrToInt(arg);

    if (val_i.has_value())
        return ConfigVariant(val_i.value());

    std::optional<float> val_fl = StrToFloat(arg);

    if (val_fl.has_value())
        return ConfigVariant(val_fl.value());

    return ConfigVariant(std::string(arg));

}

static bool KeyHasAnArgument(int argc, char **argv, int i) {
    return ((i + 1) < argc && argv[i+1][0] != '-');
}

// Return empty key if not valid
//
// NOTE: The boolean check of comparing bitmask to Type::kNone was done just
// because I couldn't make the bitmask itself as bool expression. That's now
// an excercise.
static std::string GetKey(char *arg) {
    
    std::string key(arg);
    if (key.front() != '-')
        return std::string("");

    key.erase(0,1);

    return key;
}

ArgParser::ArgParser(int argc, char **argv) {

    if (argc < 2)
        return;

    for (int i = 1; i < argc; ++i) {

        std::string key = GetKey(argv[i]); 
        if (key.empty())
            continue;

        if (KeyHasAnArgument(argc, argv, i)) {
            data_.insert({key, GetConfigVariant(argv[i+1])});

            i++;
        } else {
            data_.insert({key, ConfigVariant(true)});
        }

    }
}

std::optional<ConfigVariant> ArgParser::GetValue(std::string key) {

    for (ConfigMap::iterator it = data_.begin(); it != data_.end(); ++it)
        if (it->first == key)
            return {it->second};

    return {};

}

} // namespace orw::cfg
