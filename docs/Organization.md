# Organization

## Main Files
Silent Hill is comprised out of 3 main files. Two of which are in actuality overlays loaded by the executable. As such, those two overlays are not present in the root of the game, but instead packaged into the ``SILENT`` asset archive, under the `1ST` identifier. These 3 files are:
- The actual executable named `SLUS_007.07`, hereby referred to as `main`. The main executable in Silent Hill serves only the purpose of loading two main overlays, which contain the actual game logic.
- An overlay responsible for loading the font, the Konami splash screen an the content warning, named `B_KONAMI.BIN`, hereby referred to as `boot`.
- The overlay containing the actual game's code, named `BODYPROG.BIN`, hereby referred to as `game`.


## Structure
A simple breakdown of how this repository is structured, as it can become confusing fast.
### Source Structure
The actual decompiled source code is organized in the following way.
```
src/
├── overlays/
│   └── All overlays present in the game, sorted into dedicated folders.
├── boot/
│   └── The boot overlay, known as B_KONAMI.BIN.
├── game/
│   └── The main game logic overlay, known as BODYPROG.BIN.
└── main.c
    └── The game's main executable, known as SLUS_007.07.
```