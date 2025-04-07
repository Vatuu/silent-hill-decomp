## File Formats
The game uses a number of custom file formats to store data related to models, levels, cutscenes, and other game assets.

Some of these formats have been documented over the years, but a few still remain undocumented (or were only ever documented on long-closed-down websites).

Since the goal of this project is a matching decompilation, understanding these file formats is essential, and may also help shape the decompilation process.

### Data Files
The table below summarizes each file format encountered so far, their known or suspected purposes, and any available documentation or parsing tools.

> [!NOTE]  
> Many formats are still being reversed/inferred during the decompilation process. Contributions of parsers, template definitions, or observations are welcome!

| File Type | Purpose | Parser/Documentation |
|-|-|-|
| .ANM | Animation data | - |
| .BIN | Overlay code, loaded into memory when needed by the game. | - |
| .CMP | Unknown, found in 'TEST' folder, compressed? | - |
| .DAT | Data for demo playback, contains button states for each frame. | - |
| .DMS | Cutscene keyframe data. | [sh1_dms.bt](/docs/file_formats/sh1_dms.bt) |
| .ILM | Skeletal models. | [sh1_models_draft.bt](https://github.com/Sparagas/Silent-Hill/blob/main/010%20Editor%20-%20Binary%20Templates/sh1_models_draft.bt) by Sparagas |
| .IPD | Local static models. | [sh1_models_draft.bt](https://github.com/Sparagas/Silent-Hill/blob/main/010%20Editor%20-%20Binary%20Templates/sh1_models_draft.bt) by Sparagas, [sh_ipd2obj](https://github.com/belek666/sh_ipd2obj) by belek666 | 
| .KDT | Konami MIDI tracker files. | [kdt-tool](https://github.com/Nisto/kdt-tool) by Nisto |
| .PLM | Global static models. | [sh1_models_draft.bt](https://github.com/Sparagas/Silent-Hill/blob/main/010%20Editor%20-%20Binary%20Templates/sh1_models_draft.bt) by Sparagas, [sh_ipd2obj](https://github.com/belek666/sh_ipd2obj) by belek666 |
| .TIM | PsyQ SDK texture container. | SDK `filefrmt.pdf` |
| .TMD | PsyQ SDK 3D models, used exclusively on the item screen. | SDK `filefrmt.pdf` |
| .VAB | PsyQ SDK audio container. | SDK `filefrmt.pdf` |
| XA/* | XA audio & FMV video. | SDK `filefrmt.pdf` |
| Savegame | Tracks players current progress in the game. | [ps1_memory_card.bt](https://github.com/Sparagas/Silent-Hill/blob/main/010%20Editor%20-%20Binary%20Templates/ps1_memory_card.bt) by Sparagas |

### `SILENT.` & `HILL.` Containers
The game keeps all of its data merged together inside the `SILENT.` and `HILL.` files on the game disc. `SILENT.` contains data/overlay files, while `HILL.` contains XA audio & video.

These containers have no header or file table inside it, instead the list of files is kept in the main executable, in a [slightly-transformed way](/src/main/filetable.c.inc).

The game itself usually refers to each file by its index in the table, and uses the table to find which sector to seek to in order to read the file.

> [!NOTE]  
> [silentassets.py](/tools/silentassets/extract.py) tool can handle parsing the file table from the retail executable and extracting from these containers.

### Folder Paths
Folder names were fortunately left included in the file table, even though game itself doesn't appear to make use of them:

| Folder Name | File Types | Purpose |
|-|-|-|
| 1ST/ | .TIM, .BIN | B_KONAMI.BIN boot logo overlay & main BODYPROG.BIN engine overlay, both encrypted with XOR key. |
| ANIM/ | .ANM, .DMS | ANM files for each character model, and .DMS files for each cutscene location. |
| BG/ | .TIM, .IPD, .BIN | Textures & models for level graphics, along with two unknown .BIN files. |
| CHARA/ | .TIM, .ILM | Textures & skeletal models for each character. |
| ITEM/ | .TIM, .TMD, .PLM | Textures & models for in-game items. |
| MISC/ | .DAT | Data related to demo playback. |
| SND/ | .KDT, .VAB | MIDI audio & audio samples. |
| TEST/ | .CMP, .DMS, .ILM, .IPD, .TIM, .TMD | Mostly leftovers from ITF, uncertain if any are used by game. |
| TIM/ | .TIM | Full-screen textures. |
| VIN/ | .BIN | Overlay binaries for maps & screens. |
| XA/ | - | XA audio banks & FMV videos. |

### Sources

https://github.com/SILENTpavel/SHresearch/blob/master/README.md

https://github.com/Sparagas/Silent-Hill/tree/main
