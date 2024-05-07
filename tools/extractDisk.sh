#!/bin/bash

basename=$1
rom_dir=$2
extract_dir=$3
asset_dir=$4
echo "Extracting ROM \"$basename\" to $extract_dir..."

(cd tools/psxiso;./dumpsxiso -x ../../$extract_dir -s ../../$extract_dir/layout.xml ../../$rom_dir/$basename.bin)
(cd tools/silentassets;python3 extract.py -exe ../../$extract_dir/SLUS_007.07 -fs ../../$extract_dir/SILENT. -fh ../../$extract_dir/HILL. ../../$asset_dir)

echo "Done!"