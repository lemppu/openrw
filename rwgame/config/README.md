# OpenRW Configuration

A rewrite of OpenRW Configuration. For the workings of previous version, see
[BACKGROUND](BACKGROUND.md).

## Idea

Other components just include header [config.h](config.h), that is a small
interface to the whole Configurator. The actual work happens in [core class]
(core.h), that uses INI-file parser and argument parser as needed and manages
the data for option values, that can be queried and changed by clients via
GetValue/SetValue interface provided by the Configurator.

Core manages one set of active configuration whose build preference, from
lowest to highest is:

* Hardcoded defaults
* Configuration file
* Command-line arguments
* Runtime adjustments

## First target

The first target is to achieve the functionality of the previous version:

* Options from hardcoded default values
* Options from INI-file
    * Saving options to INI-file
* Options from command line arguments

After that is achieved, the initial branch is proposed for Pull Request.

## Planned features

Upcoming features in planning:

* Ability to give game components the possibility to register their config
values with Configurator and set a callback, that will send those values back
when they are changed from outside. 

    * This makes it possible to have a runtime console, that can change values
immediately during the came, which could be a big advantage in development.
