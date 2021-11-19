# OpenRW Configuration

OpenRW configuration can be provided either by a command line or a settings
file in INI format.

Configuration uses Boost::program-options for parsing, but is independent of
other components in RWGame and other modules of OpenRW except RWCore from where
it loads the debug component from.

## Configuration options

Structs RWConfigLayer and RWArgConfigLayer contain the actual config options
that are generated from file RWConfig.inc by preprocessor macros.

RWArgConfigLayer is an extension of RWConfigLayer, which means that options
can be either for both command line and config file, or only for command
line.

Default config layer can be made by free function buildDefaultConfigLayer().

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

### Command line switches

| Name | Type | Category | Argument | Argument mask | Desc |
|------|------|----------|----------|---------------|------|

## Configuration classes

### RWConfigLayers

Template class to store all different configuration layers, the count of whose
is given as a template parameter in compile time.

Actual layers are stored in an internal public array called "layers". Layer can
be set by calling a templated function of setLayer with a reference to a layer
and an index number. 





Getters and missing key checkers regarding individual options are
generated from RWConfig.inc by preprocessor macros.
 - RWConfig
      - extends RWConfigLayers
 - RWArgumentParser
 - RWConfigParser

## Usage in other components

RWConfig is only used in other components in the module RWGame.


