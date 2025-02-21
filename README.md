# Silent Hill Decompilation Project

An in-progress decompilation of the 1.1 US release of Silent Hill on the Playstation 1.

## Building (Linux)

### Install build dependencies
The build process has the following package requirements:
- git
- build-essential
- binutils-mips-linux-gnu
- cpp-mips-linux-gnu
- python3
- bchunk
- 7z

Under a Debian based distribution, you can install these with the following commands:
```
sudo apt update
sudo apt install git build-essential binutils-mips-linux-gnu cpp-mips-linux-gnu python3 bchunk p7zip-full p7zip-rar
```

### Clone the repository
Clone `https://github.com/Vatuu/silent-hill-decomp` in whatever directory you wish. Make sure to clone recursively!
```
git clone --recursive https://github.com/Vatuu/silent-hill-decomp.git && cd silent-hill-decomp
```

### Install Python3 requirements
Run `pip3 install -r requirements.txt`

### Placing the ROM
Obviously, you will need to provide your own rom dump of the game. The required version is the NTSC-U 1.1 Version of Silent Hill.
If done correctly, you will end up with a .BIN and .CUE file. Both of these need to be placed inside the `rom/image` folder, and renamed to SLUS-00707.bin/.cue respectively.
SHA1 Hashes:
- .cue: `299D08DCB44E7516F394C3DD5BA40690AE33FD22` 84 Bytes
- .bin: `34278D31D9B9B12B3B5DB5E45BCBE548991ECBC7` 616,494,480 Bytes / 587 MiB

### Build the code
Run `make setup` to extract needed assets/code from the bin, if that succeeds, run `make` to build it.
Once build has finished a folder will be produced with the name `build`, inside this, you will find the output.

Additional Make Commands:
* `check`: builds the executable/overlays and makes a checksums comprobation comparing it with the original file
* `build-c`: clears the configuration of the project without deleting files
* `build-C`: clears the configuration of the project without deleting files and, after compilation, makes a checksums comprobation comparing it with the original file

`build-c/build-C` are obligatory in case of modifing the configuration in the `Makefile` in case of wanting to work on screen overlays and the maps overlays

## Contributing
Contributions are welcome. If you would like to reserve a function, open a PR with the function or file name(s).

## Big TODOs
Currently, capstone has no logic to disassemble GTE instructions (which are COP2 instructions,) and thus, these are interpreted as data. This means that any code that uses these are effectively not possible to decompile back into C (for now).
