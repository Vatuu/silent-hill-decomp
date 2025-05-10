#!/usr/bin/env python3

# maptool.py main mode compares ASM of funcs in map1 folder against funcs in map2, and prints matching filenames.
# Funcs are compared by removing any block-comments and data/func refs, and then checking Levenshtein distance.
# Any with distance = 0 will then be printed.
#
# If a matching func is found which is named as sharedFunc_XXXXXXXX_0_s00 in map1 folder (where 0_s00 is map number, eg. map0_s00)
# It'll also print out lines to add in map2 sym.txt file and #includes to add in .c file, to allow the func to be shared.
#
# maptool also allows parsing/listing map file headers, and searching map files for specific character IDs
#
# Usage: maptool.py [options] [map1] [map2]
#
# Map comparison options (map1/map2 required):
#   --matchings              Only compare map1 'matchings' against map2 'nonmatchings'
#   --nonmatchings           Only compare map1 'nonmatchings' against map2 'nonmatchings'
#   If none of above are set, will compare both against map2 'nonmatchings'
#   --replace                Replace INCLUDE_ASM for 'sharedFunc' funcs in map2 .c with #include
#   --updsyms                Update and reorder map2 sym.txt with shared functions
#
# Map header options:
#   --list [MAP_NAME]        List character spawns from MAP_NAME map headers
#   --searchChara [CHAR_ID]  Search and list any maps that contain CHAR_ID
#
# (more info at https://github.com/Vatuu/silent-hill-decomp/issues/74#issuecomment-2816256817)

import os
import re
import Levenshtein
import sys
import struct
from dataclasses import dataclass
from typing import List

e_ShCharacterId = [
    "Chara_None",
    "Chara_Hero",
    "Chara_AirScreamer",
    "Chara_NightFlutter",
    "Chara_Groaner",
    "Chara_Wormhead",
    "Chara_LarvalStalker",
    "Chara_Stalker",
    "Chara_GreyChild",
    "Chara_Mumbler",
    "Chara_HangedScratcher",
    "Chara_Creaper",
    "Chara_Romper",
    "Chara_UnusedChicken",
    "Chara_Splithead",
    "Chara_Floatstinger",
    "Chara_PuppetNurse",
    "Chara_DummyA",
    "Chara_PuppetDoctor",
    "Chara_DummyB",
    "Chara_Twinfeeler",
    "Chara_Bloodsucker",
    "Chara_Incubus",
    "Chara_Unknown23",
    "Chara_MonsterCybil",
    "Chara_LockerDeadBody",
    "Chara_Cybil",
    "Chara_EndingCybil",
    "Chara_Cheryl",
    "Chara_Cat",
    "Chara_Dahlia",
    "Chara_EndingDahlia",
    "Chara_Lisa",
    "Chara_BloodyLisa",
    "Chara_Alessa",
    "Chara_GhostChildAlessa",
    "Chara_Incubator",
    "Chara_BloodyIncubator",
    "Chara_Kaufmann",
    "Chara_EndingKaufmann",
    "Chara_Flauros",
    "Chara_LittleIncubus",
    "Chara_GhostDoctor",
    "Chara_IntensiveCareUnit",
    "Chara_Null"
]
Chara_Count = 45

def charaName(i, includeNum: bool = True):
    charName = e_ShCharacterId[i] if i < len(e_ShCharacterId) else f"Chara_Unknown{i}"
    if includeNum:
        return f"{i:>2} {charName}"
    return charName

def q20_12(value):
    return round(value / 4096.0, 3)
    
def q4_12(value):
    return round(value / 4096.0 * 360, 3)

def count_lines_in_file(file_path):
    try:
        with open(file_path, 'r') as file:
            return sum(1 for _ in file)
    except Exception as e:
        print(f"Error reading {file_path}: {e}")
        return -1

def find_shared_data_lines(text):
    """
    Checks each line in `text` for sharedData_, returning each line number and sharedData var name

    Args:
        text (str): The input multiline string.

    Returns:
        dict[int, str]: Dictionary with line numbers as keys and the first matched string as value.
    """
    pattern = r'sharedData_[a-fA-F0-9]{8}_[0-9]{1}_[a-zA-Z0-9]{3}'
    result = {}

    lines = text.splitlines()
    for i, line in enumerate(lines):
        if " + 0x" in line:
            continue # line contains offset, skip it
        match = re.search(pattern, line)
        if match:
            result[i + 1] = match.group(0)

    return result

def match_shared_data_vars(text, shared_data_map):
    """
    For each line number in shared_data_map, searches the corresponding line in text
    for the pattern D_[8 chars] and associates it with the sharedData_ value.

    Args:
        new_text (str): A multiline string to scan for D_ patterns.
        shared_data_map (dict[int, str]): Output from find_first_shared_data().

    Returns:
        list[tuple[str, str]]: List of unique (D_ pattern, sharedData_ value) tuples.
    """
    d_pattern = r'D_[a-zA-Z0-9]{8}'
    result_dict = {}

    lines = text.splitlines()
    for line_num, shared_data_val in shared_data_map.items():
        if 1 <= line_num <= len(lines):
            line = lines[line_num - 1]
            matches = re.findall(d_pattern, line)
            for match in matches:
                if match not in result_dict:
                    result_dict[match] = shared_data_val

    return list(result_dict.items())

def parse_sym_comments(content):
    comment_map = {}
    # Split the string into individual lines
    lines = content.strip().splitlines()

    for line in lines:
        # Use regex to extract variable name and comment
        match = re.match(r'\s*(\w+)\s*=.*?;\s*//\s*(.*)', line)
        if match:
            var_name = match.group(1)
            comment = match.group(2)
            comment_map[var_name] = comment

    return comment_map

def sort_sym_by_address(input_text):
    lines = input_text.strip().splitlines()
    addr_dict = {}

    for line in lines:
        if "0x" in line:
            try:
                addr_str = line.split("0x")[1].split(";")[0]
                addr = int(addr_str, 16)
                addr_dict[addr] = line
            except (IndexError, ValueError):
                continue  # skip lines that don't match the pattern

    sorted_lines = [addr_dict[addr] for addr in sorted(addr_dict.keys())]
    return "\n".join(sorted_lines)

def read_file(path):
    try:
        with open(path, 'r') as file:
            text = file.read()
            return text
    except Exception as e:
        print(f"Error reading {path}: {e}")
        return None

def clean_file(content):
    if content is None:
        return None
    # Remove /* blockquote comments */
    content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
    # Remove func_[8 chars], sharedFunc_[8 chars]_[digit]_[3 chars], L[8 chars], jtbl_[8 chars]
    content = re.sub(r'func_[a-fA-F0-9]{8}', 'func', content)
    content = re.sub(r'sharedFunc_[a-fA-F0-9]{8}_[0-9]{1}_[a-zA-Z0-9]{3}', 'func', content)
    content = re.sub(r'L[a-fA-F0-9]{8}', 'L', content)
    content = re.sub(r'jtbl_[a-fA-F0-9]{8}', 'jtbl', content)

    # Remove D_[8 chars], shared_[8 chars]_[digit]_[3 chars], along with optional "+ 0xXX" offset
    content = re.sub(
        r'sharedData_[a-fA-F0-9]{8}_[0-9]_[a-zA-Z0-9]{3}(?:\s*\+\s*0x[0-9a-fA-F]+)?',
        'D',
        content
    )
    content = re.sub(
        r'D_[a-fA-F0-9]{8}(?:\s*\+\s*0x[0-9a-fA-F]+)?',
        'D',
        content
    )
    return content

def find_equal_asm_files(searchType, map1, map2, maxdistance, replaceIncludeAsm, updateSymTxtFile):
    map1_asm_path = os.path.join("asm", "maps", map1)
    map2_asm_path = os.path.join("asm", "maps", map2)

    path1 = os.path.join(map1_asm_path, searchType, map1)
    path2 = os.path.join(map2_asm_path, "nonmatchings", map2)
    path3 = ""

    if searchType == "all":
        path1 = os.path.join(map1_asm_path, "nonmatchings", map1)
        path3 = os.path.join(map1_asm_path, "matchings", map1)
    
    if not os.path.isdir(path1):
        print(f"First path not found: {path1}")
        return
    
    if not os.path.isdir(path2):
        print(f"Second path not found: {path2}")
        return

    if path3 and not os.path.isdir(path2):
        print(f"Third path not found: {path3}")
        return
    
    # Count lines in .s files from path1
    line_counts1 = {
        os.path.join(path1, f): count_lines_in_file(os.path.join(path1, f))
        for f in os.listdir(path1) if f.endswith('.s')
    }
    
    # If "all", also count lines in "matchings" and merge into line_counts1
    if searchType == "all":
        matchings_counts = {
            os.path.join(path3, f): count_lines_in_file(os.path.join(path3, f))
            for f in os.listdir(path3) if f.endswith('.s')
        }
        line_counts1.update(matchings_counts)

    # Count lines in .s files from path2
    line_counts2 = {
        os.path.join(path2, f): count_lines_in_file(os.path.join(path2, f))
        for f in os.listdir(path2) if f.endswith('.s')
    }
    
    # Find matching line counts
    matched_files = []
    for file1, count1 in line_counts1.items():
        for file2, count2 in line_counts2.items():
            if count1 == count2 and count1 != -1:
                matched_files.append((file1, file2, count1))
                
    # symbols to add to sym.xxx.txt
    sharedFuncSymbols = {}

    # include lines to add to .c file
    includeLines = ""

    # search-replace changes to make inside .c file, if --replace is specified
    replacements = {}
    
    if matched_files:
        print(f"Matches for distance <= {maxdistance}:")
        for file1, file2, count in matched_files:
            
            # Read and clean the contents
            file1_text = read_file(file1)
            file2_text = read_file(file2)
            content1 = clean_file(file1_text)
            content2 = clean_file(file2_text)
            
            if content1 is not None and content2 is not None:
                # Compute Levenshtein distance
                distance = Levenshtein.distance(content1, content2)
                if distance <= maxdistance:

                    relative_file1 = os.path.relpath(file1, map1_asm_path)
                    relative_file2 = os.path.relpath(file2, map2_asm_path)
                    name_file1 = os.path.basename(file1)
                    name_file2 = os.path.basename(file2)

                    print(f"  {relative_file1} and {relative_file2}: {distance}")

                    # If first map file contains sharedData_ lines, try to find the D_ reference on the same line # inside second map, and build up symbol list
                    shared_data_refs = find_shared_data_lines(file1_text)
                    if len(shared_data_refs):
                        matched_data = match_shared_data_vars(file2_text, shared_data_refs)
                        for key, value in matched_data:
                            addr = key.split("_")[1]
                            addr_int = int(addr, 16)
                            if addr_int not in sharedFuncSymbols:
                                sharedFuncSymbols[addr_int] = value

                    # If first dir func is named sharedFunc, print symbol names/includes for user to add to second map
                    if "sharedFunc" in name_file1:
                        funcName = name_file1.split(".")[0]
                        addr = name_file2.split("_")[1]
                        addr = addr.split(".")[0]
                        addr_int = int(addr, 16)
                        
                        if addr_int not in sharedFuncSymbols:
                            sharedFuncSymbols[addr_int] = funcName

                        include_key = f'INCLUDE_ASM("asm/maps/{map2}/nonmatchings/{map2}", func_{addr});'
                        include_value = f'#include "maps/shared/{funcName}.h" // 0x{addr}'
                        includeLines += "\n" + include_value
                        replacements[include_key] = include_value

        if sharedFuncSymbols:
            print(f"\nsym.{map2}.txt adds:")
            for addr_int in sorted(sharedFuncSymbols.keys()):
                print(f"{sharedFuncSymbols[addr_int]} = 0x{addr_int:08X}; // type unknown, use --updsyms to read sym.{map1}.txt")

        if includeLines:
            print("\n.c includes:")
            print(includeLines)

        # Optional replacement in .c file
        if replacements and replaceIncludeAsm:
            c_path = f"src/maps/{map2}/{map2}.c"
            print(f"\nReplacing INCLUDE_ASM lines inside {c_path}...\n")
            try:
                with open(c_path, "r", encoding="utf-8") as f:
                    c_code = f.read()

                replaced = False
                for key, value in replacements.items():
                    if key in c_code:
                        c_code = c_code.replace(key, value)
                        print(f"Old: {key}\nNew: {value}\n")
                        replaced = True
                    else:
                        print(f"Could not find line to replace: {key}")

                if replaced:
                    with open(c_path, "w", encoding="utf-8") as f:
                        f.write(c_code)
                    print(f"Updated {c_path} with new includes.")
                else:
                    print(f"\nNo matching INCLUDE_ASM lines found in {c_path}. Nothing replaced.")

            except FileNotFoundError:
                print(f"\nError: File {c_path} not found.")

        # Optional sym.[map2].txt update
        if updateSymTxtFile and sharedFuncSymbols:

            file1_sym_path = f"configs/maps/sym.{map1}.txt"
            file1_sym_text = read_file(file1_sym_path)
            file1_syms = parse_sym_comments(file1_sym_text)

            sym_path = f"configs/maps/sym.{map2}.txt"
            print(f"\nAdding symbol lines to {sym_path}...\n")
            try:
                with open(sym_path, "r", encoding="utf-8") as f:
                    sym_code = f.read()

                updated = False
                for sym_addr in sorted(sharedFuncSymbols.keys()):
                    sym_addr_text = f"0x{sym_addr:08X}"
                    sym_name = sharedFuncSymbols[sym_addr]
                    if sym_addr_text not in sym_code:
                        if sym_name in file1_syms:
                            sym_line = f"{sym_name} = {sym_addr_text}; // {file1_syms[sym_name]}"
                            sym_code = sym_code + "\n" + sym_line
                            print(f"Added line: {sym_line}")
                            updated = True
                        else:
                            print(f"Symbol {sym_name} not found in sym.{map1}.txt?")
                    else:
                        print(f"Address 0x{addr_text} already has symbol defined")

                if updated:
                    sym_code = sort_sym_by_address(sym_code)
                    sym_code += "\n" # end file with newline
                    with open(sym_path, "w", encoding="utf-8") as f:
                        f.write(sym_code)
                    print(f"\nUpdated {sym_path}.")
                else:
                    print(f"\nNothing added to {sym_path}.")

            except FileNotFoundError:
                print(f"\nError: File {sym_path} not found.")
    else:
        print("\nNo matching files found.")
        
# Map header related code
        
OFFSET_mapOverlayHeader = 4
OFFSET_charaUpdateFuncs = 0x194
OFFSET_charaGroupIds = 0x248
OFFSET_charaSpawns = 0x24C

MapBasePath = "assets/VIN/"

@dataclass
class CharaSpawn:
    posX: float
    posZ: float
    chara_type: int
    rot: int
    anim_unchanged_flag: int
    unk: int

@dataclass
class MapHeader:
    update_funcs: List[int]
    group_charas: List[int]
    chara_spawns: List[CharaSpawn]

def MapHeader_Read(filepath: str) -> MapHeader:
    filepath = MapBasePath + filepath.upper()
    with open(filepath, "rb") as f:
        f.seek(0, os.SEEK_END)
        file_size = f.tell()

        # Ensure the file has at least 0x400 bytes
        if file_size < 0x400:
            return None

        f.seek(0)
        
        f.seek(OFFSET_mapOverlayHeader + OFFSET_charaUpdateFuncs)
        update_funcs = []
        for i in range(Chara_Count):
            value = struct.unpack("<I", f.read(4))[0]
            update_funcs.append(value)

        f.seek(OFFSET_mapOverlayHeader + OFFSET_charaGroupIds)
        data = f.read(4)
        group = list(data)

        f.seek(OFFSET_mapOverlayHeader + OFFSET_charaSpawns)
        chara_spawns = []
        for i in range(32):
            data = f.read(12)
            posX, chara_type, rot, anim_flag, unk, posZ = struct.unpack("<ibBbbi", data)
                         
            # When chara_type is 0 chara ID is taken from the group section, group[0] if current spawn id is 15 or below, group[1] if 16 or above
            if chara_type == 0:
                chara_type = group[1] if i >= 16 else group[0]
            
            chara_spawns.append(
                CharaSpawn(q20_12(posX), q20_12(posZ), chara_type, q4_12(16 * rot), anim_flag, unk)
            )

        return MapHeader(update_funcs=update_funcs, group_charas=group, chara_spawns=chara_spawns)

def MapHeader_Print(map_header: MapHeader):
    if map_header.update_funcs:
        print("charaUpdateFuncs_194:")
        for index, funcAddr in enumerate(map_header.update_funcs):
            if funcAddr != 0:
                print(f"  {charaName(index)} = 0x{funcAddr:08X}")
        print()

    if map_header.group_charas:
        print("charaGroupIds_248:")
        for index, charaId in enumerate(map_header.group_charas):
            if index == 0:
                group_str = "  0 - 15: "
            elif index == 1:
                group_str = " 16 - 31: "
            else:
                if charaId == 0:
                    continue # Skip empty extra entries
                if index == 2:
                    group_str = "Extra[2]: "
                else:
                    group_str = "Extra[3]: "
            print(f"  {group_str}{charaName(charaId)}")
        print()

    if map_header.chara_spawns:
        print("charaSpawns_24C:")
        for index, spawn in enumerate(map_header.chara_spawns):
            if spawn.anim_unchanged_flag != 0 or spawn.posX != 0 or spawn.posZ != 0 or spawn.rot != 0:

                # func_80037F24 only seems to count as valid if anim_unchanged_flag != 0   
                unused_text = "" if spawn.anim_unchanged_flag != 0 else " (flag == 0, slot unused?)"
                print(f"  [{index:>2}] {charaName(spawn.chara_type)} = "
                      f"({spawn.posX},{spawn.posZ}) rot {spawn.rot} "
                      f"flag 0x{spawn.anim_unchanged_flag:X} unk 0x{spawn.unk:X}{unused_text}")
                      
def MapHeader_SearchForChara(charaId: int):
    print(f"Searching for chara {charaName(charaId)}...\n")
    
    for filename in os.listdir(MapBasePath):
        if filename.lower().startswith("map") and filename.lower().endswith(".bin"):  # Only process .bin files
            map_header = MapHeader_Read(filename)
            if map_header is None:
                continue # Skip empty map files (mapT/mapX)
                
            # Check if any spawns/updatefuncs/group are setup for this chara ID
            foundIn = ""
            for index, funcAddr in enumerate(map_header.update_funcs):
                if index == charaId and funcAddr != 0:
                    foundIn += f"updateFuncs(0x{funcAddr:08X}) "
                    break
            for groupId in map_header.group_charas:
                if groupId == charaId:
                    foundIn += "charaGroupIds "
                    break
            for spawn in map_header.chara_spawns:
                if spawn.chara_type == charaId:
                    foundIn += "charaSpawns "
                    break
            if foundIn:
                print(f"Found {charaName(charaId, False)} in {filename} - {foundIn}")
                
def print_usage():
    print(f"Usage: maptool.py [options] [map1] [map2]")
    print()
    print("Map comparison options (map1/map2 required):")
    print("  --matchings              Only compare map1 'matchings' against map2 'nonmatchings'")
    print("  --nonmatchings           Only compare map1 'nonmatchings' against map2 'nonmatchings'")
    print("  If none of above are set, will compare both against map2 'nonmatchings'")
    print("  --replace                Replace INCLUDE_ASM for 'sharedFunc' funcs in map2 .c with #include")
    print("  --updsyms                Update and reorder map2 sym.txt with shared functions")
    print()
    print("Map header options:")
    print("  --list [MAP_NAME]        List character spawns from MAP_NAME map headers")
    print("  --searchChara [CHAR_ID]  Search and list any maps that contain CHAR_ID")
    
def main():
    import argparse

    parser = argparse.ArgumentParser(
        description="Find matching functions between two map folders.",
        add_help=False
    )
    
    parser.add_argument("map1", type=str, help="First map folder", nargs='?', default=None)
    parser.add_argument("map2", type=str, help="Second map folder", nargs='?', default=None)
    parser.add_argument("-h", "--help", action="store_true", help="Show this help message and exit")
    parser.add_argument("--matchings", action="store_true", help="Only compare map1 `matchings` against map2 `nonmatchings`")
    parser.add_argument("--nonmatchings", action="store_true", help="Only compare map1 `nonmatchings` against map2 `nonmatchings`")
    parser.add_argument("--replace", action="store_true", help="Replace INCLUDE_ASM with #include for shared funcs")
    parser.add_argument("--updsyms", action="store_true", help="Update and reorder sym.txt with shared functions")
    
    parser.add_argument("--list", action="store_true", help="List character spawns from map headers")
    parser.add_argument("--searchChara", type=int, help="Search all maps for character ID")
    
    args = parser.parse_args()
    
    if args.help:
        print_usage()
        return
    
    if args.searchChara is not None:
        MapHeader_SearchForChara(args.searchChara)
        
    elif args.list:
        input_file = args.map1
        if not input_file.endswith(".bin") and not input_file.endswith(".BIN"):
            input_file += ".bin"
        print(f"Reading {MapBasePath + input_file.upper()}\n")
        map_header = MapHeader_Read(input_file)
        MapHeader_Print(map_header)
        
    else:
        if args.map1 is None:
            print_usage()
            print()
            print("error: map1 argument is required for map comparison")
            return
        if args.map2 is None:
            print_usage()
            print()
            print("error: map2 argument is required for map comparison")
            return
            
        searchType = "all"
        if args.matchings:
            searchType = "matchings"
        if args.nonmatchings:
            searchType = "nonmatchings"

        if args.map2 == "all":
            TARGET_MAPS = [
                "map0_s00", "map0_s01", "map0_s02",
                "map1_s00", "map1_s01", "map1_s02", "map1_s03", "map1_s04", "map1_s05", "map1_s06",
                "map2_s00", "map2_s01", "map2_s02", "map2_s03", "map2_s04",
                "map3_s00", "map3_s01", "map3_s02", "map3_s03", "map3_s04", "map3_s05", "map3_s06",
                "map4_s00", "map4_s01", "map4_s02", "map4_s03", "map4_s04", "map4_s05", "map4_s06",
                "map5_s00", "map5_s01", "map5_s02", "map5_s03",
                "map6_s00", "map6_s01", "map6_s02", "map6_s03", "map6_s04", "map6_s05",
                "map7_s00", "map7_s01", "map7_s02", "map7_s03",
            ]
            for map_name in TARGET_MAPS:
                if map_name != args.map1:
                    find_equal_asm_files(searchType, args.map1, map_name, 0, args.replace, args.updsyms)
        else:
            find_equal_asm_files(searchType, args.map1, args.map2, 0, args.replace, args.updsyms)
            
if __name__ == "__main__":
    main()
