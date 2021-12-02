# Silent Hill Decompilation Project

An in-progress decompilation of the 1.1 US release of Silent Hill on the Playstation 1.

## Building (Linux)

### Install build dependencies
The build process has the following package requirements:
- git
- build-essential
- binutils-mips-linux-gnu
- python3
- bchunk
- 7z

Under a Debian based distribution, you can install these with the following commands:
```
sudo apt update
sudo apt install git build-essential binutils-mips-linux-gnu python3 bchunk p7zip-full p7zip-rar
```

### Clone the repository
Clone `https://github.com/Vatuu/silent-hill-decomp` in whatever directory you wish. Make sure to initialize the submodules!
```
git clone https://github.com/Vatuu/silent-hill-decomp.git --recursive
cd silent-hill-decomp
git submodule init
```

### Install Python3 requirements
Run `pip3 install requirements.txt`

### Placing the ROM
Obviously, you will need to provide your own rom dump of the game. The required version is the NTSC-U 1.1 Version of Silent Hill.
If done correctly, you will end up with a .BIN and .CUE file. Both of these need to be placed inside the `rom/image` folder, and renamed to SLUS-00707.BIN/.CUE respectively.
SHA1 Hashes:
- .CUE: `299D08DCB44E7516F394C3DD5BA40690AE33FD22` 84 Bytes
- .BIN: `34278D31D9B9B12B3B5DB5E45BCBE548991ECBC7` 616,494,480 Bytes / 587 MiB

### Build the code
Just run `make` to build. If the build succeeds, a folder will be produced with the name `build`, inside this, you will find the output.

## Contributing
Contributions are welcome. If you would like to reserve a function, open a PR with the function or file name(s).

## Big TODOs
Currently, capstone has no logic to disassemble GTE instructions (which are COP2 instructions,) and thus, these are interpreted as data. This means that any code that uses these are effectively not possible to decompile back into C (for now).
