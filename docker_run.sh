#!/bin/bash

# Check if a command was provided
if [ $# -eq 0 ]; then
    echo "Error: No command provided."
    echo "Usage: $0 <command> (e.g., make, make clean)"
    exit 1
fi

docker run --platform linux/amd64 -it --rm -v "$(pwd)":/app -w /app sh-decomp-buildenv "$@"
