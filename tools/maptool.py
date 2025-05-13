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

MapVramAddress = 0x800C9578

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
    "Chara_DummyNurse",
    "Chara_PuppetDoctor",
    "Chara_DummyDoctor",
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
    "Chara_Parasite",
    "Chara_Null"
]
Chara_Count = 45

def charaName(i, includeNum: bool = True):
    charName = e_ShCharacterId[i] if i < len(e_ShCharacterId) else f"Chara_Unknown{i}"
    if includeNum:
        return f"{i:>2} {charName}"
    return charName

def q19_12(value):
    return round(value / 4096.0, 3)
    
def q3_12(value):
    return round(value / 4096.0 * 360, 3)

def count_lines_in_file(file_path):
    glabelStr = "glabel "
    try:
        with open(file_path, 'r') as file:
            count = 0
            start_counting = False

            for line in file:
                if start_counting:
                    count += 1
                elif glabelStr in line:
                    start_counting = True  # Start counting after the glabel line

            return count
    except Exception as e:
        print(f"Error reading {file_path}: {e}")
        return -1

def find_shared_data_lines(text, funcName):
    """
    Checks each line in `text` for sharedData_, returning each line number and sharedData var name

    Args:
        text (str): The input multiline string.

    Returns:
        dict[int, str]: Dictionary with line numbers as keys and the first matched string as value.
    """
    pattern = r'sharedData_[a-fA-F0-9]{8}_[0-9]{1}_[a-zA-Z0-9]{3}'
    result = {}

    # If we have glabel then only return contents following it (in case .rodata/jtbls preceed the func)
    glabelStr = "glabel " + funcName
    index = text.find(glabelStr)
    if index != -1:
        text = text[index + len(glabelStr):].strip()

    lines = text.splitlines()
    for i, line in enumerate(lines):
        if " + 0x" in line:
            continue # line contains offset, skip it
        match = re.search(pattern, line)
        if match:
            result[i + 1] = match.group(0)

    return result

def match_shared_data_vars(text, shared_data_map, funcName):
    """
    For each line number in `shared_data_map`, searches the corresponding line in `text`
    for the pattern D_[8 chars], and associates it with the `shared_data_map` value.

    Args:
        new_text (str): A multiline string to scan for D_ patterns.
        shared_data_map (dict[int, str]): Output from find_first_shared_data().

    Returns:
        list[tuple[str, str]]: List of unique (D_ pattern, sharedData_ value) tuples.
    """
    d_pattern = r'D_[a-zA-Z0-9]{8}'
    result_dict = {}

    # If we have glabel then only return contents following it (in case .rodata/jtbls preceed the func)
    glabelStr = "glabel " + funcName
    index = text.find(glabelStr)
    if index != -1:
        text = text[index + len(glabelStr):].strip()

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

def fetch_jtbl_size(mapName, jtbl_name):
    target_dir = os.path.join("asm", "maps", mapName, "data")
    target_dlabel = f"dlabel {jtbl_name}"
    target_size = f".size {jtbl_name}"

    for root, _, files in os.walk(target_dir):
        for filename in files:
            if filename.endswith(".rodata.s"):
                filepath = os.path.join(root, filename)
                with open(filepath, "r", encoding="utf-8") as f:
                    lines = f.readlines()

                dlabel_index = -1
                size_index = -1

                for i, line in enumerate(lines):
                    if target_dlabel in line:
                        dlabel_index = i
                    elif dlabel_index != -1 and target_size in line:
                        size_index = i
                        break

                if dlabel_index != -1 and size_index != -1:
                    line_count = size_index - dlabel_index - 1
                    return line_count * 4 # each jtbl entry is 4 bytes

    return None  # jtbl not found

def fetch_jtbl_file_offset(jtbl_name):
    try:
        hex_part = jtbl_name.split('_')[1]
        value = int(hex_part, 16)
        offset = value - MapVramAddress # maps begin at 0x800C9578
        return offset
    except (IndexError, ValueError):
        return None

def insert_jtbl_to_config(mapName, jtblName):
    # Kinda ugly func to parse config yaml, since we can't rely on python yaml packages to keep the layout of our config files :/
    #
    # This func parses each subsegment in config yaml, then inserts a rodata segment for the jtbl
    # If jtbl offset + jtbl size doesn't equal the next segment, a new "rodata" segment is then added

    jtbl_offset = fetch_jtbl_file_offset(jtblName)
    if jtbl_offset is None:
        print(f"insert_jtbl_to_config: error fetching offset of {mapName} {jtblName}")
        return False

    jtbl_size = fetch_jtbl_size(mapName, jtblName)
    if jtbl_offset is None or jtbl_size is None:
        print(f"insert_jtbl_to_config: error fetching size of {mapName} {jtblName}")
        return False

    config_path = os.path.join("configs", "maps", f"{mapName}.yaml")

    with open(config_path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    output_lines = []
    in_subsegments = False
    subsegment_lines = []
    subsegment_start_idx = 0

    # First pass: extract subsegments block
    for i, line in enumerate(lines):
        stripped = line.strip()
        if stripped.startswith("subsegments:"):
            in_subsegments = True
            subsegment_start_idx = i
            output_lines.append(line)  # include the subsegments: line
            continue

        if in_subsegments:
            if not stripped.startswith("- ["):
                in_subsegments = False
                continue
            subsegment_lines.append((i, line))

    # Parse entries as (offset, line_index, line_text)
    parsed_segments = []
    for idx, line in subsegment_lines:
        try:
            start = line.index("[") + 1
            end = line.index("]")
            items = line[start:end].split(",")
            offset = int(items[0].strip(), 16)
            parsed_segments.append((offset, idx, line))
        except Exception:
            pass  # leave invalid lines alone

    # Insert jtbl and optional rodata filler entry
    jtbl_entry = f"      - [0x{jtbl_offset:X}, .rodata, {mapName}]\n"
    jtbl_end = jtbl_offset + jtbl_size
    offsets = [entry[0] for entry in parsed_segments]
    inserted = False
    filler_needed = True

    for i in range(len(parsed_segments)):
        cur_offset, _, _ = parsed_segments[i]
        if cur_offset > jtbl_offset:
            parsed_segments.insert(i, (jtbl_offset, -1, jtbl_entry))
            inserted = True

            if jtbl_end != cur_offset:
                filler_line = f"      - [0x{jtbl_end:X}, rodata]\n"
                parsed_segments.insert(i + 1, (jtbl_end, -1, filler_line))
            else:
                filler_needed = False
            break

    if not inserted:
        parsed_segments.append((jtbl_offset, -1, jtbl_entry))
        if filler_needed:
            filler_line = f"      - [0x{jtbl_end:X}, rodata]\n"
            parsed_segments.append((jtbl_end, -1, filler_line))

    # Sort and reconstruct the subsegment block
    parsed_segments.sort(key=lambda x: x[0])
    new_subsegment_lines = [entry[2] for entry in parsed_segments]

    # Reassemble full file
    result_lines = (
        lines[:subsegment_start_idx + 1]
        + new_subsegment_lines
        + lines[subsegment_start_idx + 1 + len(subsegment_lines):]
    )

    with open(config_path, "w", encoding="utf-8") as f:
        f.writelines(result_lines)

    return True

def read_file(path):
    try:
        with open(path, 'r') as file:
            text = file.read()
            return text
    except Exception as e:
        print(f"Error reading {path}: {e}")
        return None

def clean_file(content, funcName):
    if content is None:
        return None

    # If we have glabel then only return contents following it (in case .rodata/jtbls preceed the func)
    glabelStr = "glabel " + funcName
    index = content.find(glabelStr)
    if index != -1:
        content = content[index + len(glabelStr):].strip()

    # Remove /* blockquote comments */
    content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
    # Remove func_[8 chars], sharedFunc_[8 chars]_[digit]_[3 chars], L[8 chars], jtbl_[8 chars]
    content = re.sub(r'func_[a-fA-F0-9]{8}', 'func', content)
    content = re.sub(r'sharedFunc_[a-fA-F0-9]{8}_[0-9]{1}_[a-zA-Z0-9]{3}', 'func', content)
    content = re.sub(r'L[a-fA-F0-9]{8}:', 'L', content) # first try stripping any that have ":" appended
    content = re.sub(r'L[a-fA-F0-9]{8}', 'L', content) # then remove any labels that didn't have ":"
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

    # Remove jlabel text, so we can compare properly against matched C versions that are missing it
    content = content.replace("jlabel ", "")

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

    # jtbls to add to config file
    jtbl_list = {}
    
    if matched_files:
        print(f"Matches for distance <= {maxdistance}:")
        for file1, file2, count in matched_files:

            relative_file1 = os.path.relpath(file1, map1_asm_path)
            relative_file2 = os.path.relpath(file2, map2_asm_path)
            name_file1 = os.path.basename(file1)
            name_file2 = os.path.basename(file2)
            funcname_file1 = os.path.splitext(name_file1)[0]
            funcname_file2 = os.path.splitext(name_file2)[0]
            
            # Read and clean the contents
            file1_text = read_file(file1)
            file2_text = read_file(file2)
            content1 = clean_file(file1_text, funcname_file1)
            content2 = clean_file(file2_text, funcname_file2)
            
            if content1 is not None and content2 is not None:
                # Compute Levenshtein distance
                distance = Levenshtein.distance(content1, content2)
                if distance <= maxdistance:

                    print(f"  {relative_file1} and {relative_file2}: {distance}")

                    # If first map file contains sharedData_ lines, try to find the D_ reference on the same line # inside second map, and build up symbol list
                    shared_data_refs = find_shared_data_lines(file1_text, funcname_file1)
                    if len(shared_data_refs):
                        matched_data = match_shared_data_vars(file2_text, shared_data_refs, funcname_file2)
                        for key, value in matched_data:
                            addr = key.split("_")[1]
                            addr_int = int(addr, 16)
                            if addr_int not in sharedFuncSymbols:
                                sharedFuncSymbols[addr_int] = value


                    # If first dir func is named sharedFunc, print symbol names/includes for user to add to second map
                    if "sharedFunc" in name_file1:
                        addr = name_file2.split("_")[1]
                        addr = addr.split(".")[0]
                        addr_int = int(addr, 16)
                        
                        if addr_int not in sharedFuncSymbols:
                            sharedFuncSymbols[addr_int] = funcname_file1

                        include_key = f'INCLUDE_ASM("asm/maps/{map2}/nonmatchings/{map2}", func_{addr});'
                        include_value = f'#include "maps/shared/{funcname_file1}.h" // 0x{addr}'
                        includeLines += "\n" + include_value
                        replacements[include_key] = include_value

                        # If second map file2_text contains jtbls, add to our jtbl list
                        pattern = r'jtbl_[0-9a-fA-F]{4,8}'
                        for match in re.findall(pattern, file2_text):
                            jtbl_name = f"{match}"
                            if jtbl_name not in jtbl_list:
                                jtbl_list[jtbl_name] = funcname_file2

        if sharedFuncSymbols:
            print(f"\nsym.{map2}.txt adds:")
            for addr_int in sorted(sharedFuncSymbols.keys()):
                print(f"{sharedFuncSymbols[addr_int]} = 0x{addr_int:08X};")

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

                    if jtbl_list:
                        print(f"\nAdding jtbls to configs/maps/{map2}.yaml...")
                        for jtbl, func_name in jtbl_list.items():
                            print(f"  {func_name} -> {jtbl}")
                            insert_jtbl_to_config(map2, jtbl)

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
    positionX: float
    positionZ: float
    charaId: int
    rotationY: int
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
            positionX, charaId, rotationY, anim_flag, unk, positionZ = struct.unpack("<ibBbbi", data)
                         
            # When charaId is 0 chara ID is taken from the group section, group[0] if current spawn id is 15 or below, group[1] if 16 or above
            if charaId == 0:
                charaId = group[1] if i >= 16 else group[0]
            
            chara_spawns.append(
                CharaSpawn(q19_12(positionX), q19_12(positionZ), charaId, q3_12(16 * rotationY), anim_flag, unk)
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
            if spawn.anim_unchanged_flag != 0 or spawn.positionX != 0 or spawn.positionZ != 0 or spawn.rotationY != 0:

                # func_80037F24 only seems to count as valid if anim_unchanged_flag != 0   
                unused_text = "" if spawn.anim_unchanged_flag != 0 else " (flag == 0, slot unused?)"
                print(f"  [{index:>2}] {charaName(spawn.charaId)} = "
                      f"({spawn.positionX},{spawn.positionZ}) rotY {spawn.rotationY} "
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
                if spawn.charaId == charaId:
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
