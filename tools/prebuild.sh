#!/bin/bash

# prebuild.sh [target_name]

# Splat `lib` segments only support loading .o from inside .a file
# Loading .a has issues with dependency checks though
# For now, rewrite the ld linker scripts from splat to load loose .o instead

if [ "$1" == "main" ]; then
    sed -i 's/\.a:/\//g' linkers/USA/main.ld
    sed -i 's/\.a:/\//g' linkers/JAP0/main.ld
elif [ "$1" == "bodyprog" ]; then
    sed -i 's/\.a:/\//g' linkers/USA/bodyprog.ld
elif [ "$1" == "screens/stream" ] || [ "$1" == "stream" ]; then
    sed -i 's/\.a:/\//g' linkers/USA/screens/stream.ld
fi
