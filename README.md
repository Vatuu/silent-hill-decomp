# FFVII
[![Match Status](https://img.shields.io/badge/matched-0.00-brightgreen.svg)]()
[![Decomp Status](https://img.shields.io/badge/decompiled-0.00-yellow.svg)]()

An in-progress decompilation of the original US release of Final Fantasy VII on the PSX.

## Building (Linux)

### Install build dependencies
The build process has the following package requirements:
- git
- build-essential
- binutils-mips-linux-gnu
- python3

Under a Debian based distribution, you can install these with the following commands:
```
sudo apt-get update
sudo apt-get install git build-essential binutils-mips-linux-gnu python3
```

### Clone the repository
Clone `https://github.com/Drahsid/ffvii.git` in whatever directory you wish. Make sure to initialize the submodules!
```
git clone https://github.com/Drahsid/ffvii.git --recursive
cd ffvii
git submodule init
```

### Install Python3 requirements
Run `pip3 install requirements.txt`

### Extracting the contents of the disks
Currently, you have to manually rip the relevant files, and place them into the SCUS_941 directory.

To extract the required files to build, rip the bootloader from any of this disks (it is identical on all of them) and put it in the SCUS_941 directory with the name `SCUS_941`. On disk 1, this is `SCUS_941.63`; on disk 2, this is `SCUS_941.64`; on disk 3, this is `SCUS_941.65`

Once you have done this, you can then run `make setup` to extract the data and disassembly from the code and overlays.

### Build the code
Just run `make` to build. If the build succeeds, a folder will be produced with the name `build`, inside this, you will find the output.

## Contributing
Contributions are welcome. If you would like to reserve a function, open a PR with the function or file name(s).

## Big TODOs
Currently, capstone has no logic to disassemble GTE instructions (which are COP2 instructions,) and thus, these are interpreted as data. This means that any code that uses these are effectively not possible to decompile back into C (for now).

Furthermore, you have to extract the code from the disk manually. It would be most reasonable to extract the assets and data from the disk, and recreate it during the build process.


