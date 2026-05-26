# Game Information
A collection of all sorts of relevant information regarding the setup, dependencies, environment, etc. of the game.

## SDK

- Psy-Q version 4.4.0, with some 4.3.0 / 4.3.1 libraries, based on SDK `printver` output: [versions.txt](https://github.com/Vatuu/silent-hill-decomp/tree/master/lib/versions.txt)

- The **Official Playstation Magazine Demo 16 (U)/OPM16** uses a previous version of the SDK.

- Sony `safechk.obj` is used on certain releases to display a "console has been modified" error when a non-stealth modchip is installed (even on legit copies of the game!). Code for this is located inside `HP_SAFE1` and `S__SAFE2` overlay files that are encrypted and LZSS-compressed, with the two overlay files having very slight changes between them.

## Libraries

- Sound library `libsd`/`libsmf`: Supports custom Konami `KDT1` MIDI files. This library was used for some PlayStation 1 and 2 Konami games with tweaks among each game. Additionally, Silent Hill 2's SOUNDCD.IRX and SOUNDHD.IRX files appear to be from the same library.

- Math library: Contains custom `sin`/`cos` lookup-table implementation along with several `RotMatrix` functions.

- Movie player `MOVIESYS`: Based on slightly customized Psy-Q SDK sample code and used across several Konami PSX titles, along with the non-playable SLED-01774 SH1 demo disc.

## File Formats

Game uses a mixture of custom file formats and some PSY-Q/Sony proprietary formats, more information in [File Formats](https://github.com/Vatuu/silent-hill-decomp/wiki/File-Formats) document.

## Game Builds

_Silent Hill_ had several releases across different regions, some pre-release demos were also distributed to the public, along with prototypes and press builds that were later made available online.

All known releases are listed in the table below. The [silentassets](https://github.com/Vatuu/silent-hill-decomp/tree/master/tools/silentassets/extract.py) tool can extract data from each version included here.

There are also some **unverified or undumped versions**, such as the _Hong Kong/Asia_ release seen in some collections. These are listed in the **Unknown Releases** section.

### Known Releases

> [!NOTE]  
> This repo only targets the **Silent Hill (U) v1.1** release, though other releases may provide insights into parts of the code or include code/data which may be useful for the decompilation.

| Date (YY-MM-DD) | Title | Game/disc code | Notes |
|-|-|-|-|
|  | **Partial Demos** |  |  |
| 98-10-19 | Official Playstation Magazine Demo 16 (U) | SCUS-94278 | WKS.XE/XAS.XE containers, Built with debug strings enabled. |
| 98-11-06 | Famitsuu Wave 2gatsu-gou Vol. 7 (J) | SLPM-80366 | WKS./XAS. containers. |
| 98-11-06 | Silent Hill Trial Version (J) | SLPM-80363 | AKA Silent Hill Taikenban. |
| 98-12-09 | Silent Hill Demo (G) | SLED-01774 | Demo video, only `MOVIESYS`/`movie_main` code. |
| 98-12-16 | Silent Hill Demo (E) | SLED-01735 | - |
| 99-01-16 | Silent Hill Demo CD (U) | SLUS-90050 | Built with debug strings enabled. |
| 99-06-08 | Playstation Zone CD Vol. 10 (G) | SLED-02190 | WKS./XAS. containers, later reissued as `SCED-02420` & `SCED-04082` |
| 99-06-16 | Silent Hill Demo (E) | SLED-02186 | - |
|  | **Prototypes** |  |  |
| 98-11-24 | Silent Hill Preview (U) | SLUS-45678 | WKS. container, includes `FILEINFO.H`, volume dated 98-10-24? Built with debug strings enabled. |
| 99-01-07 | Silent Hill Review (U) | SLUS-00707 | WKS. container. |
| 99-01-17 | Silent Hill Trade Demo (U) | SLUS-80707 | Anti-modchip code inside `KONAMI.BIN`. |
| 99-01-22 | Silent Hill Beta (U) | SLUS-00707 | "Russian Bootleg", possibly scene pre-release. |
|  | **Final Versions** |  |  |
| 99-01-26 | Silent Hill (J) | SLPM-86192 | Rev 0, calls anti-modchip code inside `HP_SAFE1`/`S__SAFE2` files. |
| 99-02-10 | Silent Hill (U) | SLUS-00707 | v1.1 |
| 99-06-02 | Silent Hill (J) | SLPM-86192 | Rev 1, fixed Larval Stalker / Aglaophotis glitch. |
| 99-06-07 | Silent Hill (E) | SLES-01514 | - |
| 99-06-16 | Silent Hill (J) | SLPM-86192 | Rev 2 `Konami the Best` release. EXE matches Rev 1, but SILENT contents differ. Redump mentions "anti-modchip"? |

### Unknown Releases

- **Undumped HK/Asia Release**: A `SCPS-45380` disc for Hong Kong/Asia was also produced, but is currently listed online as undumped. Does the data match one of the JP versions, or was it a special release? Apparently was published by Sony rather than Konami (no Konami `VX131-XX` ID on disc), release date may have been around 1999-04.
- **NTSC Scene Releases**: Earliest known scene release is `Silent_Hill_USA_PAL_NTSC_Patch-PARADOX` dated 1999-02-05, ~2 weeks after "Silent Hill Beta (U)", but 6 days prior to the creation of US v1.1. Could they have released a patch for the "beta" only 2 weeks after it was produced, or was this for an even earlier release?
- **NTSC-J Scene Releases**: Earliest JP scene release is `Silent_Hill_JAP_Final-DVNpSX` dated 1999-05-01, one month prior to creation of JP Rev. 1. The group never used `Final` in any other releases, implying this was meant to replace an earlier non-final scene release, but at this point JP Rev. 0 was the only known JP release that would have been available. Was there an earlier release this was meant to replace?
- Scene history for 1998 is very incomplete (dat listing sites only show 8 releases for the whole year). There could be other releases about which information is missing.
