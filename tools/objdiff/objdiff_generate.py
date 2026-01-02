from pathlib import Path
from argparse import ArgumentParser
from dataclasses import dataclass, asdict
from elftools.elf.elffile import ELFFile
import logging
import yaml
import json
import sys
import re

@dataclass
class UnitMetadata:
    progress_categories: list[str]
    source_path: str

@dataclass
class Unit:
    name: str
    base_path: str
    target_path: str
    metadata: UnitMetadata
    symbol_mappings: dict[str, str]

@dataclass
class ProgressCategory:
    id: str
    name: str

@dataclass
class Config:
    build_base: bool
    build_target: bool
    custom_make: str
    custom_args: list[str]
    units: list[Unit]
    progress_categories: list[ProgressCategory]


def _create_config():
    parser = ArgumentParser()
    parser.add_argument("config", type = Path)
    parser.add_argument("version", type = str)
    parser.add_argument("--ninja", action="store_true")
    args = parser.parse_args()

    if not args.config.exists() or args.config.is_dir() or args.config.suffix != ".yaml":
        raise ValueError(f"The given path {args.objects} is not pointing towards a valid config.")

    global is_ninja
    is_ninja = (args.ninja) or False
    
    global game_version
    game_version = (args.version)
    
    with open(args.config) as stream:
        try:
            return yaml.safe_load(stream)
        except yaml.YAMLError as exc:
            raise exc

def _read_symbols_from_elf(path: Path):
    addr_to_name = {}
    with open(path, 'rb') as f:
        elffile = ELFFile(f)

        for section in elffile.iter_sections():
            if not hasattr(section, 'iter_symbols'):
                continue
            for sym in section.iter_symbols():
                if sym['st_info']['type'] != 'STT_FUNC':
                    continue  # skip non-function symbols
                addr = sym['st_value']
                name = sym.name
                if addr != 0 and name:  # skip undefined/empty
                    addr_to_name[addr] = name
    return addr_to_name

def _normalize_suffixed_symbols(path: Path):
    """Scan elf for symbols with numeric suffixes, return a dictionary of non-suffix -> suffix pairs"""
    symbols = _read_symbols_from_elf(path)
    suffix_pattern = re.compile(r'\.(\d+)$')
    normalized = {}

    for name in symbols.values():
        match = suffix_pattern.search(name)
        if match:
            base_name = name[: match.start()]  # strip the .<digits> suffix
            normalized[base_name] = name

    return normalized

EXCLUDED_NAMES = {"data", "rodata", "sdata", "bss"}

def _collect_objects(path: Path, config) -> list[Path]:
    ignored = config["ignored_files"]
    return [
        path for path in path.rglob("*.o")
        if not any(name in path.name for name in EXCLUDED_NAMES ) and not any(file in str(path) for file in ignored)
    ]

def _determine_categories(path: Path, config) -> tuple[UnitMetadata, str]:
    modified_path = path.relative_to(config["expected_paths"][game_version]).as_posix()
    if game_version == "ALL":
        modified_path = re.sub(r"^(USA|EUR|JAP[0-2])/", "", str(modified_path))

    categories = []
    for category in config["categories"]:
        for prefix in category["paths"]:
            if str(modified_path).startswith(prefix):
                categories.append(category["id"])
    fixed_ext = re.sub( r'\.(s|c).o$', '', modified_path)
    
    if game_version != "ALL":
        return (UnitMetadata(categories, f"src/{fixed_ext}.c"), fixed_ext, "")
    else:
        return (UnitMetadata(categories, f"src/{fixed_ext}.c"), fixed_ext, re.search(r"/(USA|EUR|JAP[0-2])/", str(path))[0])

def main():
    logging.basicConfig(level = logging.INFO)
    config = _create_config()
    
    expected_objects = _collect_objects(Path(config["expected_paths"][game_version]), config)
    
    ignore_base_paths = ["."]
    
    logging.info(f"Accounting for {len(expected_objects)} objects.")
    units = []
    build_method = str
    for file in expected_objects:
        processed_path = _determine_categories(file, config)
        input_path = Path(processed_path[1]).as_posix()
        if game_version != "ALL":
            base_path = f"build/{game_version}/src/{input_path}.c.o"
        else:
            base_path = f"build{processed_path[2]}src/{input_path}.c.o"
            input_path = f"{processed_path[2][1:]}{input_path}"
            
        
        # Create mappings for clone/disambiguation symbol suffixes in base object
        # (disabled as objdiff report doesn't appear to support symbol mappings right now)
        #symbol_mappings = _normalize_suffixed_symbols(base_path) if Path(base_path).exists() else {}
        symbol_mappings = {}
        
        if is_ninja:
            unit = Unit(
                input_path,
                base_path,
                str(file.as_posix()),
                processed_path[0],
                symbol_mappings)
            build_method = "ninja"
        else:
            unit = Unit(
                input_path,
                base_path,
                str(file),
                processed_path[0],
                symbol_mappings)
            build_method = "make"
        units.append(unit)
    
    categories = []
    for category in config["categories"]:
        categories.append(ProgressCategory(category["id"], category["name"]))
    
    with (Path(config["output"])).open("w") as json_file:
        json.dump(asdict(Config(False, False, build_method, ["progress", f"GAME_VERSION={game_version}"] if build_method != "ninja" and game_version != "ALL" else None, units, categories)), json_file, indent=2)

if __name__ == "__main__":
    main()