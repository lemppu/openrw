#ifndef OPENRW_CONFIG_H_
#define OPENRW_CONFIG_H_

/*
 * OpenRW Configuration
 *
 * There is a single configuration object held by the Game object. It will
 * provide configurable values for the whole program. 
 *
 * Configuration can read game settings from the command line or configuration
 * file. It provides also hardcoded defaults so that the game is usable even
 * without any configuration file or command line arguments. 
 *
 * Configuration also provides an interface where other game components 
 * (input, render etc.) can provide its options to be configurable by the user.
 */

#include <string>
#include <memory>
#include <optional>
#include <variant>
#include <vector>
#include <functional>

namespace orw::cfg {

// Type of configuration option. A single option can be of multiple types and
// given as bit flags, ie. for an option that can be set in command line and 
// configuration file, but not in the menu or runtime, the setting would be
// (kCmdLine | kIniFile)
//
// We use classic enum instead of enum class to get implicit int for bitwise
// operations. This is also why we put it in a separate namespace to get
// a feel of scoping and avoid namespace pollution.
namespace type {
enum {

    // Option can be set from command line. Command line has a precedence over
    // config file and default values.
    kCmdLine = 0x01,

    // Option can be loaded from and saved to an INI-file.
    kIniFile = 0x02,

    // Option will be modifiable by visual configuration menu.
    kUsrMenu = 0x04,

    // Option can be set in runtime via game console.
    kRunTime = 0x08,

    // If set, the option is of boolean value.
    // If not set, the option will have an argument.
    kBool = 0x10,

    // All of the above. Mostly useful to save space in cases where all
    // the flags are set.
    kAll = 0x1f

};
}

// Functions that have a return value will return one of these.
enum class Result {
    kOk,
    kFail,
    kNoSuchKey,
    kNoSuchOption,
    kInvalidValueType,
    kComponentAlreadyRegistered,
    kNoSuchComponent
};

// For the readability we alias the std::variant to ConfigVariant, that will
// accept all of the types used in the configuration.
using ConfigVariant = std::variant<std::string, float, int, bool>;

// We store possible data types in an enum, which will be a parameter of
// ConfigOption. It can be used to verify that the ConfigVariant is of correct
// data type.
enum class ValueType : unsigned int {
    kString,
    kFloat,
    kInt,
    kBool
};

// Free function to verify that the variant type holds the correct value type. 
bool VerifyValueType(ConfigVariant variant, ValueType type);

// Configurable options. Hardcoded default values provided in [core.h].
//
// When the client components register with the Configurator, they provide a list of 
// these structs to tell about their configurable values. 
struct ConfigOption {
    const std::string name;
    const std::string component_name;
    const std::string description;
    const std::vector<std::string> keys;
    const int option_type;
    const ValueType value_type;
    const ConfigVariant default_value;
    ConfigVariant current_value;
};


// Clients can register themselves to Configurator by providing a struct that
// contain their identification string and a callback function that is called
// by the Configurator when it receives an update to the option registered by
// client.
struct ConfigClient {
    std::string client_name;
    std::function<Result(ConfigOption option)> callback;
};

// We use the "Pimpl idiom" to hide the implementation details, so that there
// would be less dependencies for the clients, and more freedom to develop
// component internals without breaking userspace.
//
// Here we forward declare the Core class to be used in private definitions of 
// Configurator. The actual definition used by internal implementation files
// is found in [core.h]
class Core;

/*
 * Configurator manages all of the configurable settings of the game.
 *
 * The instance of this class is the first instance created in the program run.
 * It takes the command line arguments as constructor parameters and the actual
 * game object is created with a Configurator object as a parameter.
 *
 * Configuration values can be read and written with key/value pairs. This
 * makes it possible to change values easily in runtime, which can be a big
 * asset for development and tuning of values.
 *
 * The creation of Configurator should never fail. In case of missing or faulty
 * command line or file options, there are hardcoded defaults that will get the
 * program started. There would only be warnings in the log.
 */
class Configurator {

public:

    Configurator(int argc, char **argv);
    ~Configurator();

    std::optional<ConfigVariant> GetValue(std::string component,
                                          std::string name);

    Result SetValue(std::string component,
                    std::string name, 
                    ConfigVariant value);

    Result RegisterClient(ConfigClient client,
                          std::vector<ConfigOption> options);

    Result UnregisterClient(std::string client_name);

private:

    std::unique_ptr<Core> core_;

};

} // namespace orw::cfg

#endif // OPENRW_CONFIG_H_
