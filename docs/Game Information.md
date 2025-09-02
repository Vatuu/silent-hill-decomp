# Game Information
A collection of all sorts of relevant information regarding the setup, dependencies, environment, etc. of the game.

## SDK

- Psy-Q Version: 4.3.0 based on https://github.com/lab313ru/psx_psyq_signatures
- The **Official Playstation Magazine Demo 16 (U)/OPM16** uses an previous version of the SDK.

## Libraries

- Sound library `libsd`: Supports custom Konami `KDT1` MIDI files. This library was used for some PlayStation 1 and 2 Konami games with tweaks among each game. Additionally, Silent Hill 2's SOUNDCD.IRX and SOUNDHD.IRX files appear to be from the same library.

- Math library: Contains custom `sin`/`cos` lookup-table implementation along with several `RotMatrix` functions.

- Movie player `MOVIESYS`: Based on slightly customized Psy-Q SDK sample code and used across several Konami PSX titles, along with the non-playable SLED-01774 SH1 demo disc.

## File Formats

Game uses a mixture of custom file formats and some PSY-Q/Sony proprietary formats, more information in [File Formats](/docs/File%20Formats.md) document.

## Known Releases

Several pre-release demos and versions were released during development. A table of known releases is listed below. The [silentassets](/tools/silentassets/extract.py) tool supports extracting from each version listed here.

> [!NOTE]  
> This repo only targets the **Silent Hill (U) v1.1** release, though other releases give insights into parts of the code or include code/data which may be useful for the decompilation.

| Date (YY-MM-DD) | Title | Game/disc code | Notes |
|-|-|-|-|
|  | **Partial Demos** |  |  |
| 98-10-19 | Official Playstation Magazine Demo 16 (U) | SCUS-94278 | WKS.XE/XAS.XE containers, Built with debug features enabled. |
| 98-11-06 | Famitsuu Wave 2gatsu-gou Vol. 7 (J) | SLPM-80366 | WKS./XAS. containers. |
| 98-11-06 | Silent Hill Trial Version (J) | SLPM-80363 | AKA Silent Hill Taikenban. |
| 98-12-09 | Silent Hill Demo (G) | SLED-01774 | Demo video, only `MOVIESYS`/`movie_main` code. |
| 98-12-16 | Silent Hill Demo (E) | SLED-01735 | - |
| 99-01-16 | Silent Hill Demo CD (U) | SLUS-90050 | Built with debug features enabled. |
| 99-06-08 | Playstation Zone CD Vol. 10 (G) | SLED-02190 | WKS./XAS. containers, later reissued as `SCED-02420` & `SCED-04082` |
| 99-06-16 | Silent Hill Demo (E) | SLED-02186 | - |
|  | **Prototypes** |  |  |
| 98-11-24 | Silent Hill Preview (U) | SLUS-45678 | WKS. container, includes `FILEINFO.H`, volume dated 98-10-24? Built with debug features enabled. |
| 99-01-07 | Silent Hill Review (U) | SLUS-00707 | WKS. container. |
| 99-01-17 | Silent Hill Trade Demo (U) | SLUS-80707 | Redump mentions "anti-modchip"? |
| 99-01-22 | Silent Hill Beta (U) | SLUS-00707 | "Russian Bootleg", possibly scene pre-release. |
|  | **Final Versions** |  |  |
| 99-01-26 | Silent Hill (J) | SLPM-86192 | Rev 0 |
| 99-02-10 | Silent Hill (U) | SLUS-00707 | v1.1 |
| 99-06-02 | Silent Hill (J) | SLPM-86192 | Rev 1, fixed Larval Stalker / Aglaophotis glitch. |
| 99-06-07 | Silent Hill (E) | SLES-01514 | - |
| 99-06-16 | Silent Hill (J) | SLPM-86192 | Rev 2 `Konami the Best` release. EXE matches Rev 1, but SILENT contents differ. Redump mentions "anti-modchip"? |

### Unknown Releases

- A `SCPS-45380` release for Hong Kong/Asia was also produced, but has only been pictured inside sealed packaging. Did this include a normal JP disc inside it, or was it a special release? Release date was apparently around 1999-04.
- Earliest known scene release is `Silent_Hill_USA_PAL_NTSC_Patch-PARADOX` from 1999-02-05, dated ~2 weeks after "Silent Hill Beta (U)", but 6 days prior to US v1.1 creation date. Could they have released a patch for a game only 2 weeks after it was produced, or was this for an even earlier release?
- Earliest JP scene release is `Silent_Hill_JAP_Final-DVNpSX` from 1999-05-01, one month prior to JP Rev. 1 creation date. The group never used `Final` in any other releases, implying this was meant to replace an earlier non-final scene release, but at this point JP Rev. 0 was the only known JP release available. Was there an earlier release this was meant to replace?
- Scene history for 1998 is very incomplete (dat listing sites only show 8 releases for the whole year). There could be other releases about which information is missing.
