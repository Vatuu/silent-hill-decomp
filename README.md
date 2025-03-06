# Silent Hill Decompilation Project

An in-progress decompilation of the 1.1 US release of Silent Hill on the Playstation 1.

## Building (Linux/Windows)

### Install build dependencies
The build process has the following package requirements:
- git
- build-essential
- binutils-mips-linux-gnu
- cpp-mips-linux-gnu
- python3
- bchunk
- 7z

Under a Debian-based distribution (or Windows with a Debian-based WSL2 setup), you can install these with the following commands:
```
sudo apt update
sudo apt install git build-essential binutils-mips-linux-gnu cpp-mips-linux-gnu python3 bchunk p7zip-full p7zip-rar
```

### Clone the repository
Clone `https://github.com/Vatuu/silent-hill-decomp` to your desired directory. Make sure to clone recursively!
```
git clone --recursive https://github.com/Vatuu/silent-hill-decomp.git && cd silent-hill-decomp
```

### Install Python3 requirements
Run `pip3 install -r requirements.txt`

### Place the ROM
Obviously, you will need to provide your own ROM dump of the game. The required version is Silent Hill NTSC-U 1.1.
If done correctly, you will end up with a .BIN and a .CUE file. These must be placed in the `rom/image` folder and renamed to SLUS-00707.bin/.cue, respectively.
SHA1 Hashes:
- .cue: `299D08DCB44E7516F394C3DD5BA40690AE33FD22` 84 Bytes
- .bin: `34278D31D9B9B12B3B5DB5E45BCBE548991ECBC7` 616,494,480 Bytes / 587 MiB

### Build the code
Run `make setup` to extract needed assets and code from the binary.
If setup was successful, run `make` to build.
Once the build has finished, a folder will be produced with the name `build`. Inside this, you will find the output.

Additional Make commands:
* `check`: Builds the executable and overlays. After compilation, it compares checksums with the original files.
* `build-c`: Clears the configuration of the project without deleting files.
* `build-C`: Clears the configuration of the project without deleting files. After compilation, it compares checksums with the original files.

NOTE: `build-c/build-C` are obligatory if the configuration in the `Makefile` has been modified when intending to work on different overlays.

## Contributing
Contributions are welcome. Following our [code conventions](./docs/Coding Conventions.md), feel free to contribute via a pull request or issue and join us on the [PS1/PS2 Decompilation](https://discord.gg/VwCPdfbxgm) Discord server in the `#silent-hill` channel.
