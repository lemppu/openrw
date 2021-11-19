# OpenRW Configuration

OpenRW configuration can be provided by a command line and/or a settings file
in INI format.

Configuration uses `boost::program_options` for parsing, but is independent of
other components in `RWGame` and other modules of OpenRW except `RWCore`, from
where it loads the debug and platform components.

Configuration component consists of three files:

* `RWConfig.hpp` (262 lines)
* `RWConfig.cpp` (591 lines)
* `RWConfig.inc` (25 lines)

## Configuration options

Structs `RWConfigLayer` and `RWArgConfigLayer` contain the actual config
options that are generated from file `RWConfig.inc` by preprocessor macros.

`RWArgConfigLayer` is an extension of `RWConfigLayer`, which means that options
can be either from both command line and config file, or only for command
line.

Default config layer can be made by free function `buildDefaultConfigLayer()`.

### Configuration file options

These are also command line options.

| Name | Type | Default | Path | Category | Switch name | Switch argument | Desc |
|------|------|---------|------|----------|----------|---------------|------|
gameDataPath | std::string | | game.path | Config | gamedata | PATH | Path of game data
invertY | bool | false | input.invert_y | Input | invert_y |  | Invert the y-axis of the mouse
width | int | 800 | window.width | Window | width,w | WIDTH | Game resolution width in pixels
height | int | 600 | window.height | Window | height,h | HEIGHT | Game resolution height in pixels
fullscreen | bool | false | window.fullscreen | Window | fullscreen,f | | Enable fullscreen mode
hudScale | float | 1.f | game.hud_scale | Window | hud_scale | FACTOR | Scaling factor of the HUD
gameLanguage | std::string | american | game.language | Game | language | LANGUAGE | Game Language


### Command line options

| Name | Type | Category | Switch name | Switch argument | Desc |
|------|------|----------|----------|---------------|------|
configPath | std::string | Config | config,c  | PATH | Path of configuration file
noconfig | bool | Config | noconfig  | | Don't load configuration file
test | bool | Develop | test,t | | Start a new game in a test location
benchmarkPath | std::string | Develop | benchmark,b | PATH | Run benchmark from file
newGame | bool | Game | newgame,n | | Start a new game
loadGamePath | std::string | Game | load,l | PATH | Load save file
help | bool | General | help | | Show help message

## Configuration classes

### Public classes

Defined in `RWConfig.hpp`

#### RWConfigLayers

Template class to store all different configuration layers, the count of whose
is given as a template parameter in compile time.

Actual layers are stored in an internal public array `layers`. Layer can
be set by calling a templated function `setLayer` with a reference to a layer
and an index number. The function is implemented in the header file and there
is no guard for the index.

The class contains a template function `get()`, which creates a function
pointer to get a value of every option that has one. The function is
implemented in header file and the instances of it are generated from
`RWConfig.inc` by preprocessor macros.

A function that returns a list of missing keys is also implemented in header
file and is generated from `RWConfig.inc` by preprocessor macros.

#### RWConfig

Class that implements `RWConfigLayers` with four separate layers.

##### Definition

The layers are defined as an enum inside the class:

| Enum | Value |
|------|-------|
LAYER_USER | 0
LAYER_ARGUMENT | 1
LAYER_CONFIGFILE | 2
LAYER_DEFAULT | 3

Even though LAYER_USER is defined, it's never used. *NOTE:* _should there be
any difference between USER and CONFIGFILE?_

The class also has public `std::map<std::string, std::string> unknown`.

#### RWArgumentParser

Class to parse command line arguments.

##### Definition

The class has private member `desc` of type
`boost::program_options::options_description`.

There is an internal enum `Category`:

| Enum | Value |
|------|-------|
CONFIG | 0
GAME | 1
INPUT | 2
WINDOW | 3
DEVELOP | 4
GENERAL | 5

The class has parameterless constructor, a copy constructor and a move
constructor.

Help can be printed with method `printHelp()` to the output stream provided
by user.

Actual parsing is done by calling method
`parseArguments(int argc, const char **argv)` that returns std::optional of
type `RWArgConfigLayer`.

##### Implementation

TODO

#### RWConfigParser

##### Definition

Class to parse configuration file.

It provides a static function `getDefaultConfigPath()` to read file from
default location.

Function `loadFile()` takes an argument for `std::filesystem::path` and
returns a tuple of `RWConfigLayer` and `RWConfigParser::ParseResult`.

There are also two methods for `saveFile()` to save given layer to given
file. Another of them has also a parameter for
`std::map<std::string, std::string>` called `extra`.

Given layer can be made into string by method `layerToString()`.

##### Implementation

TODO

#### ParseResult

Internal public class for `RWConfigParser` and a _friend_ class to it.

##### Definition

The class has both public and private members defined in two separate places.

There is public enum `ErrorType` for configuration errors:

| Enum | Value |
|------|-------|
UNINITIALIZED | 0
GOOD | 1
INVALDIINPUTFILE | 2
INVALIDCONTENT | 3
INVALIDOUTPUTFILE | 4

Method `type()` returns error status of the instance.

Method `getKeysInvalidData()` returns keys with invalid data.

`markGood()` can be called to mark the result instance as valid.

`failInputFile()` can be called with a line number and message in case of
error in the input file.

`failInvalidData()` can be called with a key to indicate an invalid key.

`failOutputFile()` can be calles when there is an error in writing tu the
output.

`isValid()` boolean to check whether the result is valid.

`what()` returns a string of the error state in the instance.

`setUnknownData()` can replace unknown key/value pairs.

`getUnknownData()` returns all of the unknown key/value pairs.

Private constructor `ParseResult(std::string, std::string)` can store
the issues from the parsing of config file.

Private enum `m_result` stores the type of the failure.

Private strings `m_inputfilename` and `m_outputfilename` store their
respective file names.

Private member `m_line` stores a line number of the failure in the file.

Private string `m_message` stores the description of the failure.

Private vector `m_keys_invalidData` stores all the keys containing invalid
data.

Private map `m_unknownData` stores unknown keys and their associated data.

---

### Private classes

Defined in `RWConfig.cpp`

## Usage

`RWConfig` is only used by other components in the module `RWGame`. However,
there is a bit of work to find out what components exactly use the config,
because `RWConfig.hpp` is included in `GameBase.hpp`, which is then included
by `RWGame.hpp` which is included by several components, so there's some
digging to find out all usage.

### main.cpp

At the beginning of program entry, the main function initializes
`RWArgumentParser`, checks its validity and passes it to the `RWGame`
constructor before starting the game loop.

```c++

    RWArgumentParser argParser;
    auto argLayerOpt = argParser.parseArguments(argc, argv);
    if (!argLayerOpt.has_value()) {
        argParser.printHelp(std::cerr);
        return 1;
    }
    if (argLayerOpt->help) {
        argParser.printHelp(std::cout);
        return 0;
    }
...
    try {
        RWGame game(logger, argLayerOpt);

        return game.run();
    }
```

### GameBase.cpp

`RWArgConfigLayer` is passed as an argument to the `GameBase` constructor,
which then builds is member `config` by calling its protected method
`buildConfig()`.

`GameBase` also provides public method `getConfig()` to get the private member
`config`.

`GameBase::buildConfig()` is a 49 line function that takes `RWArgConfigLayer`
as an argument.

If given `RWArgConfigLayer` has value, it will be a parameter to
`config.setLayer()` along with enum LAYER_ARGUMENT.

Default layer will be constructed by calling the free function
`buildDefaultConfigLayer()` and set to config by calling `setLayer()` with
LAYER_DEFAULT as a second parameter.

### RWGame.cpp


### states/DebugState.cpp

### states/IngameState.cpp

## TODO

- [ ] All of the public functions should be automatically tested with valid, error
and corner cases. Start with testing the current functionality before changing
the code.

- [ ] All of the classes are now packed into `RWConfig.cpp`. They should be
extracted into their respective translation units and moved to config/ where
they can also be tested independently.

- [ ] Public interfaces in `RWConfig.hpp` are too crowded. Public access should
be limited to only the methods used by another components and rest should be
hidden inside private classes. Clear interfaces bring clarity.

- [ ] The main logic of building the configuration layers happens now in the
class `GameBase`, but there is no reason why all of the building logic should
not happen in the component `config`. It could take command line args as a
constructor parameter and then provide a single interface of config for the
clients. All the details and configuration logic should be handled
in-component.

- [ ] Add clear namespaces to show the location of classes and functions. For
example, argument parser would be `orw::game::config::argParser` etc.

- [ ] Remove boost::program_options. Write either separate or common objects to
parse configuration options from ini-file and command line arguments.

- [ ] Parsing configuration options from `RWConfig.inc` is 'smart', but at the
expense of readability. In the end, options tend to be quite static, so they
should be defined in more readable and accessible form.
