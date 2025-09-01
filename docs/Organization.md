# Organization

## Main Files
Silent Hill is comprised out of 3 main files. The executable, and two file containers: ``SILENT.`` and ``HILL.``.

``HILL.`` exclusively contain audio and FMVs while ``SILENT.`` contains the overall game data including all the important pieces of game code which are overlays.

### Code Files Explanation
Alongside the executable, the most important pieces of code are inside the ``1ST`` folder in ``SILENT.``:
- The actual executable named `SLUS_007.07`, hereby referred to as `main`. The main executable in Silent Hill serves only the purpose of initialize the load of `B_KONAMI.BIN` and `BODYPROG.BIN` while also displaying the content warning image.
- An overlay responsible for loading the some of the assets of general the game (as it is Harry's model and animations and the fonts) and display the Konami and KTCE splash screens `B_KONAMI.BIN`.
- The overlay containing the main engine and general game code, named `BODYPROG.BIN`.

The rest of the overlays are in `VIN` folder, which include:
- `STREAM.BIN` - used to play video files.
- `OPTION.BIN` - used for displaying and handling the logic of the options menu.
- `SAVELOAD.BIN` - used for displaying and handling the logic of the save and load menu (not responsible for handling memory card state or save data, those are in charge of the engine).
- `STF_ROLL.BIN` - used to display credits.
- `MAP#_S##.BIN` - maps scripts and AI logic, loaded in the game playthrough order (e.g. `MAP0_S00.BIN` - is the first file from the game start up to the cafe, `MAP0_S01.BIN` is loaded next).
- - `_S##` can be a shortage of `STAGE`. While the second number is clearly intended to represent the stage index the first number is always 0 excepting in the European release where it uses different numbers from 0 to 5 (skipping 1 for unknown reasons) in order to represent the language.
- - There are 5 map overlays that are probably unused, those being:
- - - `MAP1_S04.BIN`
- - - `MAP2_S03.BIN`
- - - `MAP4_S04.BIN`
- - - `MAP4_S06.BIN`
- - - `MAP6_S05.BIN`

## Main Folders Structures
A simple breakdown of how this repository is structured specially intended for newbies.

### Source Folder Structure
The actual decompiled source code (excepting most of map code; See `Include Folder Structure`) is organized in the following way:
```
src/
├── maps/
│   └── map#_s##/
│       └── The map (level) scripts overlay (MAP#_S##.BIN).
├── screens/
│   ├── b_konami/
│   │   └── The boot screen overlay (B_KONAMI.BIN).
│   ├── credits/
│   │   └── The credits screen overlay (STF_ROLL.BIN).
│   ├── options/
│   │   └── The options screen overlay (OPTION.BIN).
│   ├── saveload/
│   │   └── The save/load screen overlay (SAVELOAD.BIN).
│   └── stream/
│       └── The video stream overlay (STREAM.BIN).
├── bodyprog/
│   └── The main game logic overlay (BODYPROG.BIN).
└── main/
    └── The game's main executable logic (SLUS_007.07).
```

### Include Folder Structure
The actual decompiled source code is organized in the following way:
```
include/
│   └── General game or tooling specific header files and macro defines.
├── maps/
│   └── map#/
│       └── Exclusive per-map overlay data and functions header files.
│   └── shared/
│       └── Shared decompiled functions among overlays.
├── bodyprog/
│   └── Headers for game's main game logic overlay (BODYPROG.BIN).
├── psyq/
│   └── Headers for PSY-Q SDK.
├── screens/
│   ├── b_konami/
│   │   └── Headers for the boot screen overlay (B_KONAMI.BIN).
│   ├── credits/
│   │   └── Headers for the credits screen overlay (STF_ROLL.BIN).
│   ├── options/
│   │   └── Headers for the options screen overlay (OPTION.BIN).
│   ├── saveload/
│   │   └── Headers for the save/load screen overlay (SAVELOAD.BIN).
│   └── stream/
│       └── Headers for the video stream overlay (STREAM.BIN).
└── main/
    └── Headers for game's main executable code (SLUS_007.07).
```