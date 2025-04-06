# Game Information
A collection of all sorts of relevant information regarding the setup, dependencies, environment, etc. of the game.

## SDK

- Psy-Q Version: 4.3.0 - seems to be correct, based on https://github.com/lab313ru/psx_psyq_signatures

## Libraries

- Sound library `libsd`, supporting custom Konami `KDT1` MIDI files, also seen in the unreleased Konami International Rally Racing, Silent Hill 2's SOUNDCD.IRX and SOUNDHD.IRX files also seem based around the same library.

- Math library, contains custom `sin`/`cos` lookup-table implementation along with several `RotMatrix` functions.

- Movie player `MOVIESYS`, based on slightly customized Psy-Q SDK sample code, used across several Konami PSX titles along with the non-playable SLED-01774 SH1 demo disc.

## File Formats
Several custom file formats for models/cutscenes/levels, more information in [File Formats](/docs/File%20Formats.md) document.
