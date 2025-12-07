#!/bin/bash

# prebuild.sh [target_name]

# Splat `lib` segments only support loading .o from inside .a file
# Loading .a has issues with dependency checks though
# For now, rewrite the ld linker scripts from splat to load loose .o instead

if [ "$1" == "main" ]; then
    sed -i 's/\.a:/\//g' linkers/main.ld
elif [ "$1" == "bodyprog" ]; then
    sed -i 's/\.a:/\//g' linkers/bodyprog.ld
elif [ "$1" == "screens/stream" ] || [ "$1" == "stream" ]; then
    sed -i 's/\.a:/\//g' linkers/screens/stream.ld
fi
