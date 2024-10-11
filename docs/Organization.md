# Organization

## Main Files
Silent Hill is comprised out of 3 main files. Two of which are in actuality overlays loaded by the executable. As such, those two overlays are not present in the root of the game, but instead packaged into the ``SILENT`` asset archive, under the `1ST` identifier. These 3 files are:
- The actual executable named `SLUS_007.07`, hereby referred to as `main`. The main executable in Silent Hill serves only the purpose of loading two main overlays, which contain the actual game logic.
- An overlay responsible for loading the font, the Konami splash screen an the content warning, named `B_KONAMI.BIN`.
- The overlay containing the actual game's code, named `BODYPROG.BIN`.

The rest of the overlays are in `VIN` folder, which include:
- `STREAM.BIN` - loaded when playing video files.
- `OPTION.BIN` - loaded when opening the options menu.
- `SAVELOAD.BIN` - loaded when opening save/load menu.
- `STF_ROLL.BIN` - loaded when credits are displayed.
- `MAP#_S##.BIN` - maps (or levels) scripts, loaded in the game playthrough order (e.g. `MAP0_S00.BIN` - is the first file from the game start up to the cafe, `MAP0_S01.BIN` is loaded next) - needs investigation to check which map file is responsible for which parts of the game.

## Structure
A simple breakdown of how this repository is structured, as it can become confusing fast.
### Source Structure
The actual decompiled source code is organized in the following way.
```
src/
├── screens/
│   ├── credits/
│   │   └── The credits overlay (STF_ROLL.BIN).
│   └── options/
│       └── The options screen overlay (OPTION.BIN).
├── b_konami/
│   └── The boot screen overlay (B_KONAMI.BIN).
├── bodyprog/
│   └── The main game logic overlay (BODYPROG.BIN).
├── stream/
│   └── The video stream overlay (STREAM.BIN).
└── main/
    └── The game's main executable logic (SLUS_007.07).
```