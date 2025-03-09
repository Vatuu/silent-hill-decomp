from pathlib import Path
from argparse import ArgumentParser
from dataclasses import dataclass, asdict
import logging
import json

@dataclass
class Config:
    build_base: bool
    build_target: bool
    units: list

@dataclass
class Unit:
    name: str
    base_path: Path
    target_path: Path

def _createParser():
    parser = ArgumentParser()
    parser.add_argument("objects", type = Path)
    parser.add_argument("output", type=Path)
    return parser

def main():
    logging.basicConfig(level = logging.INFO)
    args = _createParser().parse_args()

    if not args.objects.is_dir():
        raise ValueError(f"The given path {args.objects} is not directory containing object files.")

    o_files = [str(file) for file in args.objects.rglob('*.o')]
    logging.info(f"Accounting for {len(o_files)} objects.")
    units = []
    for file in o_files:
        units.append(Unit(
            file.removeprefix("expected/src/").removesuffix(".c.o"),
            "build" + file.removeprefix("expected"), 
            file))
    
    with (args.output / "objdiff.json").open("w") as json_file:
        json.dump(asdict(Config(False, False, units)), json_file, indent=2)

    #split.main(config_files,  modes="all", verbose=False)
    #segments = split.linker_writer.entries
    #for segment in segments:
    #    logging.info(f"Reading {segment}")

if __name__ == "__main__":
    main()