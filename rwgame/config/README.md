# OpenRW Configuration

OpenRW configuration can be provided either by a command line and/or a settings
file in INI format.

Configuration uses `boost::program_options` for parsing, but is independent of
other components in `RWGame` and other modules of OpenRW except `RWCore`, from
where it loads the debug and platform components.

## Configuration options

Structs `RWConfigLayer` and `RWArgConfigLayer` contain the actual config
options that are generated from file `RWConfig.inc` by preprocessor macros.

`RWArgConfigLayer` is an extension of `RWConfigLayer`, which means that options
can be either for both command line and config file, or only for command
line.

Default config layer can be made by free function `buildDefaultConfigLayer()`.

### Configuration file options

These are also command line options.

| Name | Type | Default | Path | Category | Argument | Argument mask | Desc |
|------|------|---------|------|----------|----------|---------------|------|
gameDataPath | std::string | | game.path | Config | gamedata | PATH | Path of game data
invertY | bool | false | input.invert_y | Input | invert_y |  | Invert the y-axis of the mouse
width | int | 800 | window.width | Window | width,w | WIDTH | Game resolution width in pixels
height | int | 600 | window.height | Window | height,h | HEIGHT | Game resolution height in pixels
fullscreen | bool | false | window.fullscreen | Window | fullscreen,f | | Enable fullscreen mode
hudScale | float | 1.f | game.hud_scale | Window | hud_scale | FACTOR | Scaling factor of the HUD
gameLanguage | std::string | american | game.language | GAME | language | LANGUAGE | Game Language


### Command line arguments

| Name | Type | Category | Argument | Argument mask | Desc |
|------|------|----------|----------|---------------|------|
configPath | std::string | Config | config,c | PATH | Path of configuration file
noconfig | bool | Config | noconfig | | Don't load configuration file
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

Actual layers are stored in an internal public array called "layers". Layer can
be set by calling a templated function of setLayer with a reference to a layer
and an index number. The function is implemented in the header file and there
is no guard for the index.

The class contains a template function `get()`, which creates a function
pointer to get a value of every option that has one. The function is
implemented in header file and the instances of it are generated from
`RWConfig.inc` by preprocessor macros.

A function that returns a list of missing keys is also implemented in header
file and is generated from `RWConfig.inc` by preprocessor macros.

#### RWConfig

#### RWArgumentParser

#### RWConfigParser

### Private classes

Defined in `RWConfig.cpp`

## Usage in other components

`RWConfig` is only used in other components in the module `RWGame`.

_Use cases to be listed here._

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

- [ ] Add clear namespaces to show the location of classes and functions. For
example, argument parser would be `orw::game::config::argParser` etc.

- [ ] Remove boost::program_options. Write either separate or common objects to
parse configuration options from ini-file and command line arguments.

- [ ] Parsing configuration options from `RWConfig.inc` is 'smart', but at the
expense of readability. In the end, options tend to be quite static, so they
should be defined in more readable and accessible form.
