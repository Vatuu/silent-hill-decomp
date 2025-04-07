# Game Information
A collection of all sorts of relevant information regarding the setup, dependencies, environment, etc. of the game.

## SDK

- Psy-Q Version: 4.3.0 - seems to be correct, based on https://github.com/lab313ru/psx_psyq_signatures

## Libraries

- Sound library `libsd`, supporting custom Konami `KDT1` MIDI files, also seen in the unreleased Konami International Rally Racing, Silent Hill 2's SOUNDCD.IRX and SOUNDHD.IRX files also seem based around the same library.

- Math library, contains custom `sin`/`cos` lookup-table implementation along with several `RotMatrix` functions.

- Movie player `MOVIESYS`, based on slightly customized Psy-Q SDK sample code, used across several Konami PSX titles along with the non-playable SLED-01774 SH1 demo disc.

## File Formats

Game makes use of custom file formats for models/cutscenes/levels, more information in [File Formats](/docs/File%20Formats.md) document.

## Known releases

Several pre-release demos and versions were released during development, some of the known versions are listed below, along with the tools that support each build.

> [!NOTE]  
> This repo only targets the **Silent Hill (U) v1.1** release, though other releases could give insights into parts of the code, or include code/data which may be useful for the decompilation.

| Date (YY-MM-DD) | Title | Game/disc code | [silentassets](https://github.com/Vatuu/silent-hill-decomp/blob/master/tools/silentassets/extract.py) support | [SHExtract](https://github.com/mbystryantsev/consolgames-tools/tree/master/game-specific/Silent%20Hill/FilesExtractor) support | Notes |
|-|-|-|-|-|-|
| - | **Partial Demos** | - | - | - | - |
| 98-10-19 | Official Playstation Magazine Demo 16 (U) | SCUS-94278 | :x: | :heavy_check_mark: | WKS.XE / XAS.XE containers. |
| 98-11-06 | Silent Hill Trial Version (J) | SLPM-80363 | :x: | :heavy_check_mark: | AKA Silent Hill Taikenban. |
| 98-12-09 | Silent Hill Demo (G) | SLED-01774 | - | - | Demo video, only `MOVIESYS`/`movie_main` code. |
| 98-12-16 | Silent Hill Demo (E) | SLED-01735 | :x: | :heavy_check_mark: | - |
| 99-01-16 | Silent Hill Demo CD (U) | SLUS-90050 | :x: | :heavy_check_mark: | - |
| 99-06-08 | Playstation Zone CD Vol. 10 (G) | SLED-02190 | :x: | :heavy_check_mark: | WKS./XAS. containers, later reissued as `SCED-02420` & `SCED-04082` |
| 99-06-16 | Silent Hill Demo (E) | SLED-02186 | :x: | :heavy_check_mark: | - |
| - | **Prototypes** | - | - | - | - |
| 98-11-24 | Silent Hill Preview (U) | SLUS-45678 | :heavy_check_mark: | :x: | WKS. container, includes `FILEINFO.H`, burn date 98-10-24? |
| 99-01-07 | Silent Hill Review (U) | SLUS-00707 | :x: | :x: | WKS. container. |
| 99-01-17 | Silent Hill Trade Demo (U) | SLUS-80707 | :x: | :x: | - |
| 99-01-22 | Silent Hill Beta (U) | SLUS-00707 | :x: | :x: | "Russian Bootleg", possibly scene pre-release. |
| - | **Final Versions** | - | - | - | - |
| 99-01-26 | Silent Hill (J) | SLPM-86192 | :x: | :x: | Rev 0 |
| 99-02-10 | Silent Hill (U) | SLUS-00707 | :heavy_check_mark: | :heavy_check_mark: | v1.1 |
| 99-06-02 | Silent Hill (J) | SLPM-86192 | :x: | :x: | Rev 1, fixed Larval Stalker / Aglaophotis glitch. |
| 99-06-07 | Silent Hill (E) | SLES-01514 | :heavy_check_mark: | :heavy_check_mark: | - |
| 99-06-16 | Silent Hill (J) | SLPM-86192 | :heavy_check_mark: | :heavy_check_mark: | Rev 2, `Konami the Best` release. |

### Unknown releases

- A `SCPS-45380` release for Hong Kong/Asia was also produced, but has only been pictured inside sealed packaging, did this include a normal JP disc inside it, or was it a special release? (release date was apparently around 1999-04)
- Earliest known scene release is `Silent_Hill_USA_PAL_NTSC_Patch-PARADOX` from 1999-02-05, dated ~2 weeks after "Silent Hill Beta (U)", but 6 days prior to US v1.1 creation date - could they release a patch for a game only 2 weeks after it was produced? or was this for even earlier release?
- Earliest JP scene release is `Silent_Hill_JAP_Final-DVNpSX` from 1999-05-01, 1 month prior to JP Rev. 1. `Final` implies this was meant to replace an earlier non-final release (the group never used `Final` in other releases), but at this point JP Rev. 0 was the only known release, was there an earlier release this was meant to replace?
- Scene history for 1998 is very incomplete (dat listing sites only show 8 releases for the whole year), could be other releases that we're missing information about.
