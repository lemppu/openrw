# OpenRW Configuration

OpenRW configuration can be provided either by a command line or a settings
file in INI format.

Configuration uses Boost::program-options for parsing, but is independent of
other components in RWGame and other modules of OpenRW except RWCore from where it loads the debug component from.

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
gameDataPath | std::string | null | game.path | Config | gamedata | PATH | Path of game data
invertY | bool | false | input.invert_y | Input | invert_y |  | Invert the y-axis of the mouse
width | int | 800 | window.width | Window | width,w | WIDTH | Game resolution width in pixels


### Command line arguments

| Name | Type | Category | Argument | Argument mask | Desc |
|------|------|----------|----------|---------------|------|

### Command line switches

| Name | Type | Category | Argument | Argument mask | Desc |
|------|------|----------|----------|---------------|------|

## Configuration classes

 - RWConfigLayers
 - RWConfig
      - extends RWConfigLayers
 - RWArgumentParser
 - RWConfigParser

## Usage in other components

RWConfig is only used in other components in the module RWGame.


