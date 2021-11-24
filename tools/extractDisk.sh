#!/bin/sh
config=$1

parse_yaml() {
    local prefix=$2
    local s='[[:space:]]*' w='[a-zA-Z0-9_]*' fs=$(echo @|tr @ '\034')
    sed -ne "s|^\($s\)\($w\)$s:$s\"\(.*\)\"$s\$|\1$fs\2$fs\3|p" \
        -e "s|^\($s\)\($w\)$s:$s\(.*\)$s\$|\1$fs\2$fs\3|p"  $1 |
    awk -F$fs '{
        indent = length($1)/2;
        vname[indent] = $2;
        for (i in vname) {if (i > indent) {delete vname[i]}}
        if (length($3) > 0) {
            vn=""; for (i=0; i<indent; i++) {vn=(vn)(vname[i])("_")}
            printf("%s%s%s=\"%s\"\n", "'$prefix'",vn, $2, $3);
        }
    }'
}
eval $(parse_yaml $1 "config_")

cd $config_options_base_path

basename=$config_basename
rom_dir=$config_rom_path
extract_dir=$config_rom_extraction_path
echo "Extracting ROM \"$basename\" to $extract_dir..."

bchunk $rom_dir/$basename.bin $rom_dir/$basename.cue $extract_dir/$basename > /dev/null

for i in $extract_dir/$basename*.iso; do
    echo "\tExtracting Track $i..."
    7z x -aoa -o$extract_dir $i > /dev/null
    rm -f $i
done

echo "Done!"