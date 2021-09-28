#!/usr/bin/env python3

def apply(config, args):
    config['mapfile'] = f'build/SCUS_941.map'
    config['myimg'] = f'build/SCUS_941'
    config['baseimg'] = f'SCUS_941/SCUS_941'
    config['source_directories'] = ['src', 'include', 'asm']
