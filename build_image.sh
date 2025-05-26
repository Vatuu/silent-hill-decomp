#!/bin/bash

# Build the Docker image
docker build --platform linux/amd64 -f Dockerfile -t sh-decomp-buildenv .
