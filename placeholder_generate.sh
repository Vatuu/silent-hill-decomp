#!/bin/bash

rm -rf build
rm -rf asm
rm -rf assets
rm -rf linker
rm -rf meta/*auto*.txt 
find rom -maxdepth 1 -type f -delete
bash tools/extractDisk.sh SLUS-00707 rom/image rom assets
python3 -m splat split configs/main.yaml