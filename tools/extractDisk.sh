#!/bin/sh

basename=$1
rom_dir=$2
extract_dir=$3
echo "Extracting ROM \"$basename\" to $extract_dir..."

bchunk $rom_dir/$basename.bin $rom_dir/$basename.cue $extract_dir/$basename > /dev/null

for i in $extract_dir/$basename*.iso; do
    echo "\tExtracting Track $i..."
    7z x -aoa -o$extract_dir $i > /dev/null
    rm -f $i
done

echo "Done!"