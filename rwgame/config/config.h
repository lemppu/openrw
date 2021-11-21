#ifndef OPENRW_GAME_CONFIG_H_
#define OPENRW_GAME_CONFIG_H_

/*
 * OpenRW Configuration
 *
 *
 *
 *
 */

#include <string>
#include <memory>
#include <optional>
#include <variant>

namespace orw {

namespace cfg {

    enum class Result {
        kOk,
        kFail,
        kNoSuchKey
    };

    using Value = std::variant<std::string, float, int, bool>;

    // We use the "Pimpl idiom" to hide the implementation details, so that
    // there would be less dependencies for clients, and more freedom to
    // develop component internals without breaking userspace.
    //
    // Here we forward declare the class to be used in private definitions 
    // of Configurator
    class Core;

} // namespace cfg

/*
 * Configurator manages all of the configurable settings of the game.
 *
 * The instance of this class is the first instance created in the program.
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

    std::optional<cfg::Value> GetValue(std::string key);
    // cfg::Result SetValue(std::string key, cfg::Value value);

private:

    std::unique_ptr<cfg::Core> core_;

};

} // namespace orw

#endif // OPENRW_GAME_CONFIG_H_
