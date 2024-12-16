#!/usr/bin/env python3

import os

def add_custom_arguments(parser):
    parser.add_argument(
        "--overlay",
        default="SLUS_007.07",
        dest="overlay",
        help="Defines which overlay to use for the diff (main, bodyprog, stream, b_konami, etc)",
    )

def apply_main(config, args):
    config['mapfile'] = f'build/SLUS_007.07.map'
    config['myimg'] = f'build/SLUS_007.07'
    config['baseimg'] = f'rom/image/SLUS_007.07'
    config['source_directories'] = ['src/main', 'include', 'asm/main']

def apply_overlay(binary_name, src_name, config, args):
    config['mapfile'] = f'build/{os.path.basename(binary_name)}.map'
    config['myimg'] = f'build/{os.path.basename(binary_name)}'
    config['baseimg'] = f'assets/{binary_name}'
    config['source_directories'] = [f'src/{src_name}', f'asm/{src_name}', 'include']

def apply(config, args):
    overlay = args.overlay or "SLUS_007.07"
    if overlay == "SLUS_007.07" or overlay == "main":
        apply_main(config, args)
    else:
        if overlay == "bodyprog":
            apply_overlay("1ST/BODYPROG.BIN", "bodyprog", config, args)
        elif overlay == "b_konami":
            apply_overlay("1ST/B_KONAMI.BIN", "b_konami", config, args)
        elif overlay == "stream":
            apply_overlay("VIN/STREAM.BIN", "stream", config, args)
    config["arch"] = "mipsel"
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"
