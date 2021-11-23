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
static ConfigValue GetConfigValue(const char* arg) {

    std::optional<float> val_fl = StrToFloat(arg);

    if (val_fl.has_value())
        return ConfigValue(val_fl.value());

    std::optional<int> val_i = StrToInt(arg);

    if (val_i.has_value())
        return ConfigValue(val_i.value());

    return ConfigValue(std::string(arg));

}

static bool KeyHasAnArgument(int argc, char **argv, int i) {
    return ((i + 1) < argc && argv[i+1][0] != '-');
}

// Return empty key if not valid
//
// NOTE: The boolean check of comparing bitmask to Type::kNone was done just
// because I couldn't make the bitmask itself as bool expression. That's now
// an excercise.
static std::string GetKey(std::string arg) {
    
    if (arg.front() != '-')
        return std::string("");

    arg.erase(0,1);

    for (auto it = kValidOptions.begin(); it != kValidOptions.end(); ++it)
        if (it->first == arg &&
            static_cast<unsigned int>(it->second & OptionType::kCmdLine)) 
                return arg;

    return std::string(""); 
}

static bool IsValidValue([[maybe_unused]] std::string key, [[maybe_unused]]const char *arg) {
    return true;
} 

ArgParser::ArgParser(int argc, char **argv) {

    if (argc < 2)
        return;

    for (int i = 1; i < argc; ++i) {

        std::string key = GetKey(std::string(argv[i])); 
        if (key.empty())
            continue;

        if (KeyHasAnArgument(argc, argv, i)) {
            if (IsValidValue(key, argv[i+1]))
                data_.insert({argv[i], GetConfigValue(argv[i+1])});

            i++;
        } else {
            data_.insert({argv[i], ConfigValue(true)});
        }

    }
}

std::optional<ConfigValue> ArgParser::GetValue(std::string key) {

    for (ConfigMap::iterator it = data_.begin(); it != data_.end(); ++it)
        if (it->first == key)
            return {it->second};

    return {};
}

} // namespace orw::cfg
