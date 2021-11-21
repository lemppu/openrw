# OpenRW Configuration

A rewrite of OpenRW Configuration. For the workings of previous version, see
[BACKGROUND](BACKGROUND.md).

The first target is to achieve the functionality of the previous version:

* Options from hardcoded default values
* Options from INI-file
    * Saving options to INI-file
* Options from command line arguments

After that is achieved, the initial branch is proposed for Pull Request.

Upcoming features in planning:

* Ability to give game components the possibility to register their config
values with Configurator and set a callback, that will send those values back
when they are changed from outside. 

    * This makes it possible to have a runtime console, that can change values
immediately during the came, which could be a big advantage in development.
