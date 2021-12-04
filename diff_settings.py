#!/usr/bin/env python3

def apply(config, args):
    config['mapfile'] = f'build/SLUS_007.07.map'
    config['myimg'] = f'build/SLUS_007.07'
    config['baseimg'] = f'rom/image/SLUS_007.07'
    config['source_directories'] = ['src', 'include', 'asm']
