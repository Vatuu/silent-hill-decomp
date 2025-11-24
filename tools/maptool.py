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
#   --update                 Replace INCLUDE_ASM for 'sharedFunc' funcs in map2 .c with #include, update and reorder map2 sym.txt with shared functions
#   --when [funcName]        Only apply --update if funcName has been matched in this map (to help with sub-function false-positives)
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

# Known shared-data variables names, for data that isn't named sharedData_XXX
# TODO: Not complete list atm
SharedDataVariables = [
    "MAP_POINTS",
    "MAP_ROOM_IDXS",
    "CREAPER_ANIM_INFOS",
    "STALKER_ANIM_INFOS",
    "MAP_MESSAGES",
    "g_Particle_SpeedX",
    "g_Particle_SpeedZ",
    "g_ParticleVectors0",
    "g_Particle_RotationY",
    "g_ParticleVectors1",
    "g_Particle_Position",
    "g_Particle_PrevPosition",
    "g_Particle_PrevRotationY"
]

# Funcs that have already been symbol-matched between all valid matching funcs in the project
# Will only allow code sharing for these with funcs under the same symbol name
# (workaround for some small non-related AI funcs that can have false-positive matches with these)
SymbolMatchedFuncs = [
    "sharedFunc_800D8888_0_s01",
    "sharedFunc_800D88D0_0_s01",
    "sharedFunc_800CDA88_3_s03",
    "sharedFunc_800D08FC_3_s04",
    "sharedFunc_800D0944_3_s04",
    "Ai_Lisa_Init",
    "Ai_Lisa_Update",
    "Ai_BloodyLisa_Update",
    "sharedFunc_800D595C_7_s01",
    "sharedFunc_800D59A4_7_s01",
    "sharedFunc_800D5B3C_7_s01",
    "Ai_BloodyLisa_Init",
    "sharedFunc_800D4A2C_7_s01",
    "sharedFunc_800D4A74_7_s01",
    "sharedFunc_800D4C0C_7_s01",
    "Ai_GhostChildAlessa_Init",
    "Ai_Cheryl_Init",
    "Ai_Alessa_Init",
    "Ai_Dahlia_Update",
    "sharedFunc_800CD280_2_s01",
    "sharedFunc_800CD2C8_2_s01",
    "sharedSymbol_800CD4A0_2_s01",
    "Ai_Dahlia_Init"
]

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
    "Chara_Padlock"
]
Chara_Count = 45

MapFileNames = [
    "map0_s00", "map0_s01", "map0_s02",
    "map1_s00", "map1_s01", "map1_s02", "map1_s03", "map1_s04", "map1_s05", "map1_s06",
    "map2_s00", "map2_s01", "map2_s02", "map2_s03", "map2_s04",
    "map3_s00", "map3_s01", "map3_s02", "map3_s03", "map3_s04", "map3_s05", "map3_s06",
    "map4_s00", "map4_s01", "map4_s02", "map4_s03", "map4_s04", "map4_s05", "map4_s06",
    "map5_s00", "map5_s01", "map5_s02", "map5_s03",
    "map6_s00", "map6_s01", "map6_s02", "map6_s03", "map6_s04", "map6_s05",
    "map7_s00", "map7_s01", "map7_s02", "map7_s03",
]

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
    # Pattern for sharedData_ variables
    pattern = r'sharedData_[a-fA-F0-9]{8}_[0-9]{1}_[a-zA-Z0-9]{3}'

    # Compile secondary pattern for renamed sharedData vars
    shared_vars = SharedDataVariables or []
    if shared_vars:
        # Escape special chars and join alternatives
        vars_pattern = r'(' + '|'.join(map(re.escape, shared_vars)) + r')'
    else:
        vars_pattern = None

    result = {}

    # Limit search to text after the function label (if present)
    glabelStr = "glabel " + funcName
    index = text.find(glabelStr)
    if index != -1:
        text = text[index + len(glabelStr):].strip()

    # Check each line
    lines = text.splitlines()
    for i, line in enumerate(lines):
        if " + 0x" in line:
            continue  # skip lines with offsets

        # Check for sharedData_ pattern
        match = re.search(pattern, line)
        if match:
            result[i + 1] = match.group(0)
            continue

        # Check for named shared vars
        if vars_pattern:
            match = re.search(vars_pattern, line)
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

def parse_sym_addrs(content):
    func_dict = {}

    lines = content.strip().splitlines()
    for line in lines:
        # Strip leading/trailing spaces and ignore empty lines
        line = line.strip()
        if not line or line.startswith('//'):
            continue  # Skip empty lines and full-line comments

        # Split by '='
        parts = line.split('=')
        if len(parts) != 2:
            continue  # Skip lines that don't have exactly one '='

        # Get function name and value
        func_name = parts[0].strip()
        value_part = parts[1].split('//')[0].strip()  # Ignore anything after a comment

        # Ensure value is a valid hex number
        if value_part.startswith("0x"):
            try:
                if value_part.endswith(";"):
                    value_part = value_part[:-1]
                value = int(value_part, 16)  # Convert hex string to integer
                func_dict[func_name] = value
            except ValueError:
                continue  # Skip invalid hex values
        else:
            continue  # Skip lines without a valid hex value

    return func_dict

def parse_sym_comments(content):
    comment_map = {}
    lines = content.strip().splitlines()

    for line in lines:
        # Use regex to extract variable name and comment
        match = re.match(r'\s*(\w+)\s*=.*?;\s*(?://\s*(.*))?', line)
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

    # Remove any known SharedDataVariables
    content = re.sub(r'\b(' + '|'.join(map(re.escape, SharedDataVariables)) + r')\b', 'D', content)

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

    # Remove .size directive
    content = re.sub(r'^\s*\.size.*$\n?', '', content, flags=re.MULTILINE)

    # Strip AI func refs (Ai_xxxx)
    content = re.sub(r'(Ai_[a-zA-Z_]+)(?=(,)?(\s|$))', 'func', content)

    # Remove jlabel text, so we can compare properly against matched C versions that are missing it
    content = content.replace("jlabel ", "")

    return content

def find_similar_functions(func1_path, maxDistance):
    print(f"Searching for functions similar to {func1_path} (max distance: {maxDistance})")

    maps_base_path = os.path.join("asm", "maps")

    func1_fname = os.path.basename(func1_path)
    func1_name = os.path.splitext(func1_fname)[0]

    func1_text = read_file(func1_path)
    func1_content = clean_file(func1_text, func1_name)

    # Fetch each map name into array so we can sort + loop through them alphabetically
    map_names = []
    for map_name in os.listdir(maps_base_path):
        map_path = os.path.join(maps_base_path, map_name)
        if os.path.isdir(map_path):
            map_names.append(map_name)

    # Nasty loops in loops
    map_names.sort()
    for map_name in map_names:
        map_path = os.path.join(maps_base_path, map_name)
        if os.path.isdir(map_path):
            # asm/maps/[map]/...
            for match_type in os.listdir(map_path):
                match_path = os.path.join(map_path, match_type)
                if os.path.isdir(match_path):
                    # asm/maps/[map]/[matchings]/
                    for tu_name in os.listdir(match_path):
                        tu_path = os.path.join(match_path, tu_name)
                        if os.path.isdir(tu_path):
                            # asm/maps/[map]/[matchings]/[tu]...
                            for asm_file in os.listdir(tu_path):
                                if asm_file.endswith('.s'):
                                    asm_path = os.path.join(tu_path, asm_file)
                                    func2_fname = os.path.basename(asm_file)
                                    func2_name = os.path.splitext(func2_fname)[0]
                                    if func2_name != func1_name:
                                        func2_text = read_file(asm_path)
                                        func2_content = clean_file(func2_text, func2_name)
                                        distance = Levenshtein.distance(func1_content, func2_content)
                                        if distance <= maxDistance:
                                            print(f"   {asm_path} - distance {distance}")




def find_equal_asm_files(searchType, map1, map2, maxdistance, replaceIncludeAsm, updateSymTxtFile, funcToMatchBeforeUpdating):
    map1_asm_path = os.path.join("asm", "maps", map1)
    map2_asm_path = os.path.join("asm", "maps", map2)

    path1_base = os.path.join(map1_asm_path, searchType)
    path2_base = os.path.join(map2_asm_path, "nonmatchings")
    path3_base = ""

    if searchType == "all":
        path1_base = os.path.join(map1_asm_path, "nonmatchings")
        path3_base = os.path.join(map1_asm_path, "matchings")

    if not os.path.isdir(path1_base):
        print(f"First base path not found: {path1_base}")
        return

    if not os.path.isdir(path2_base):
        print(f"Second base path not found: {path2_base}")
        return

    if path3_base and not os.path.isdir(path3_base):
        print(f"Third base path not found: {path3_base}")
        return

    # Initialize dictionaries to store line counts
    line_counts1 = {}
    line_counts2 = {}

    # Process files from path1_base (all subdirectories)
    for subdir in os.listdir(path1_base):
        subdir_path = os.path.join(path1_base, subdir)
        if os.path.isdir(subdir_path):
            for file in os.listdir(subdir_path):
                if file.endswith('.s'):
                    file_path = os.path.join(subdir_path, file)
                    line_counts1[file_path] = count_lines_in_file(file_path)

    # If "all", also process files from path3_base (all subdirectories)
    if searchType == "all" and path3_base:
        for subdir in os.listdir(path3_base):
            subdir_path = os.path.join(path3_base, subdir)
            if os.path.isdir(subdir_path):
                for file in os.listdir(subdir_path):
                    if file.endswith('.s'):
                        file_path = os.path.join(subdir_path, file)
                        line_counts1[file_path] = count_lines_in_file(file_path)

    # Process files from path2_base (all subdirectories)
    for subdir in os.listdir(path2_base):
        subdir_path = os.path.join(path2_base, subdir)
        if os.path.isdir(subdir_path):
            for file in os.listdir(subdir_path):
                if file.endswith('.s'):
                    file_path = os.path.join(subdir_path, file)
                    line_counts2[file_path] = count_lines_in_file(file_path)
    
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

            relative_file1 = os.path.relpath(file1, map1_asm_path)
            relative_file2 = os.path.relpath(file2, map2_asm_path)
            name_file1 = os.path.basename(file1)
            name_file2 = os.path.basename(file2)
            funcname_file1 = os.path.splitext(name_file1)[0]
            funcname_file2 = os.path.splitext(name_file2)[0]
            tu_file1 = os.path.normpath(relative_file1).split(os.sep)[1]
            tu_file2 = os.path.normpath(relative_file2).split(os.sep)[1]
            status_file1 = os.path.normpath(relative_file1).split(os.sep)[0]
            status_file2 = os.path.normpath(relative_file2).split(os.sep)[0]

            # If funcname_file1 is in SymbolMatchedFuncs, the project has already renamed all valid matches for this
            # So if funcname_file2 name doesn't match it must be a false positive
            if funcname_file1 in SymbolMatchedFuncs and funcname_file1 != funcname_file2:
                continue

            # If file2 funcname begins with sharedFunc and name + status (matching/nonmatching) matches with file1, skip this func
            # (most likely was already sym-shared but not yet code-matched, no point in us comparing them until they've been matched)
            if (funcname_file2.startswith("sharedFunc_") or funcname_file2.startswith("Ai_")) and status_file1 == status_file2 and funcname_file1 == funcname_file2:
                continue
            
            # Read and clean the contents
            file1_text = read_file(file1)
            file2_text = read_file(file2)
            content1 = clean_file(file1_text, funcname_file1)
            content2 = clean_file(file2_text, funcname_file2)

            file2_sym_path = f"configs/USA/maps/sym.{map2}.txt"
            file2_sym_text = read_file(file2_sym_path)
            file2_syms = parse_sym_addrs(file2_sym_text)
            
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
                    if "sharedFunc" in name_file1 or "Ai_" in name_file1 or "Event_" in name_file1:
                        addr = 0

                        # Try searching file2_syms for the addr of this func, in case this func had been renamed already
                        if funcname_file2 in file2_syms:
                            addr = file2_syms[funcname_file2]
                        else:
                            addr_str = name_file2.split("_")[1]
                            addr_str = addr_str.split(".")[0]
                            addr = int(addr_str, 16)
                        
                        if addr not in sharedFuncSymbols:
                            sharedFuncSymbols[addr] = funcname_file1

                        include_search = f'INCLUDE_ASM("asm/maps/{map2}/nonmatchings/{tu_file2}", {funcname_file2});'
                        sharedFilePath = f"maps/shared/{funcname_file1}.h"
                        if os.path.exists("include/" + sharedFilePath):
                            include_replace = f'#include "{sharedFilePath}" // 0x{addr:08X}'
                        else:
                            include_replace = f'INCLUDE_ASM("asm/maps/{map2}/nonmatchings/{tu_file2}", {funcname_file1}); // 0x{addr:08X}'

                        includeLines += "\n" + include_replace
                        replacements[include_search] = include_replace

        if sharedFuncSymbols:
            print(f"\nsym.{map2}.txt adds:")
            for addr_int in sorted(sharedFuncSymbols.keys()):
                print(f"{sharedFuncSymbols[addr_int]} = 0x{addr_int:08X};")

        if includeLines:
            print("\n.c includes:")
            print(includeLines)

        # If user specified a --when func, check if that's being added, if not then skip adding anything to this map
        if (replaceIncludeAsm and replacements) or (updateSymTxtFile and sharedFuncSymbols):
            if funcToMatchBeforeUpdating is not None:
                present = funcToMatchBeforeUpdating in sharedFuncSymbols.values() or funcToMatchBeforeUpdating in file2_syms.keys()
                if not present:
                    print(f"\n{funcToMatchBeforeUpdating} not found in this map, skipping --update");
                    return

        # Optional replacement in .c file
        if replaceIncludeAsm and replacements:
                dir_path = f"src/maps/{map2}/"
                print(f"\nReplacing INCLUDE_ASM lines in {dir_path}...\n")

                try:
                    c_files = [f for f in os.listdir(dir_path) if f.endswith(".c")]
                    any_replaced = False

                    for c_file in c_files:
                        c_path = os.path.join(dir_path, c_file)
                        with open(c_path, "r", encoding="utf-8") as f:
                            c_code = f.read()

                        replaced = False
                        for key, value in replacements.items():
                            if key in c_code:
                                c_code = c_code.replace(key, value)
                                print(f"{c_file}:\n  Old: {key}\n  New: {value}\n")
                                replaced = True

                        if replaced:
                            # Remove duplicate funcaddr comments
                            c_code = re.sub(r'(\s*//\s*(0x[a-fA-F0-9]+)\s*)\1+', r'\1', c_code)
                            with open(c_path, "w", encoding="utf-8") as f:
                                f.write(c_code)
                            print(f"Updated {c_file} with new includes.")
                            any_replaced = True

                    if not any_replaced:
                        print(f"\nNo matching INCLUDE_ASM lines found in any .c files in {dir_path}. Nothing replaced.")

                except FileNotFoundError:
                    print(f"\nError: Directory {dir_path} not found.")

        # Optional sym.[map2].txt update
        if updateSymTxtFile and sharedFuncSymbols:

            file1_sym_path = f"configs/USA/maps/sym.{map1}.txt"
            file1_sym_text = read_file(file1_sym_path)
            file1_syms = parse_sym_comments(file1_sym_text)

            print(f"\nAdding symbol lines to {file2_sym_path}...\n")
            try:
                updated = False
                for sym_addr in sorted(sharedFuncSymbols.keys()):
                    sym_addr_text = f"0x{sym_addr:08X};"
                    sym_name = sharedFuncSymbols[sym_addr]
                    if sym_addr_text not in file2_sym_text:
                        if sym_name in file1_syms:
                            if file1_syms[sym_name] is not None:
                                sym_line = f"{sym_name} = {sym_addr_text} // {file1_syms[sym_name]}"
                            else:
                                sym_line = f"{sym_name} = {sym_addr_text}"
                            file2_sym_text = file2_sym_text + "\n" + sym_line
                            print(f"Added line: {sym_line}")
                            updated = True
                        else:
                            print(f"Symbol {sym_name} not found in sym.{map1}.txt?")
                    else:
                        print(f"Address {sym_addr_text} already has symbol defined")

                if updated:
                    file2_sym_text = sort_sym_by_address(file2_sym_text)
                    file2_sym_text += "\n" # end file with newline
                    with open(file2_sym_path, "w", encoding="utf-8") as f:
                        f.write(file2_sym_text)
                    print(f"\nUpdated {file2_sym_path}.")
                else:
                    print(f"\nNothing added to {file2_sym_path}.")

            except FileNotFoundError:
                print(f"\nError: File {file2_sym_path} not found.")
    else:
        print("\nNo matching files found.")

def find_partial_shares():
    # Search map .c files for funcs in include/maps/shared which are INCLUDE_ASM instead of #include
    include_dir = "include/maps/shared"
    src_dir = "src/maps"

    # Get all filenames in include/shared without extension
    include_files = [
        os.path.splitext(f)[0]
        for f in os.listdir(include_dir)
        if os.path.isfile(os.path.join(include_dir, f))
    ]

    # Walk through all .c files under src/maps
    unique_funcs = set()
    for root, _, files in os.walk(src_dir):
        for cfile in files:
            if not cfile.endswith(".c"):
                continue
            cpath = os.path.join(root, cfile)
            with open(cpath, "r", errors="ignore") as f:
                lines = f.readlines()
                for lineno, line in enumerate(lines, start=1):
                    # Split at '//' to ignore comments
                    code_part = line.split("//", 1)[0]
                    for inc in include_files:
                        if inc in code_part and "INCLUDE_ASM" in code_part:
                            print(f"{cpath}:{lineno}: {line.strip()}")
                            unique_funcs.add(inc)

    print(f"\n{len(unique_funcs)} partially shared funcs:")
    for inc in sorted(unique_funcs):
        print(inc)
        
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
    print("  --matchings                 Only compare map1 'matchings' against map2 'nonmatchings'")
    print("  --nonmatchings              Only compare map1 'nonmatchings' against map2 'nonmatchings'")
    print("  If none of above are set, will compare both against map2 'nonmatchings'")
    print("  --update                    Replace INCLUDE_ASM for 'sharedFunc' funcs in map2 .c with #include, update and reorder map2 sym.txt with shared functions")
    print("  --when [funcName]           Only apply --update if funcName has been matched in this map (to help with sub-function false-positives)")
    print()
    print("Map header options:")
    print("  --list [MAP_NAME]           List character spawns from MAP_NAME map headers")
    print("  --searchChara [CHAR_ID]     Search and list any maps that contain CHAR_ID")
    print()
    print("Misc:")
    print("  --sortsyms [MAP_NAME]       Sort map symbols ('all' to sort all map symbol files)")
    print("  --compareFuncs [FUNC1_ASM_PATH] [FUNC2_ASM_PATH]    Compare two functions, print Levenshtein distance, write clean files for comparing")
    print("  --similar [MAX_DIFF] [FUNC_ASM_PATH]   Search for funcs similar to FUNC_ASM_PATH, with max difference of MAX_DIFF")
    print("  --partial                   Search map .c files for funcs in include/maps/shared which are INCLUDE_ASM instead of #include")

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
    parser.add_argument("--update", action="store_true", help="Replace INCLUDE_ASM with #include for shared func, update and reorder sym.txt with shared functions")
    parser.add_argument("--when", type=str, help="Only apply --update if funcName has been matched in this map")
    
    parser.add_argument("--list", action="store_true", help="List character spawns from map headers")
    parser.add_argument("--searchChara", type=int, help="Search all maps for character ID")

    parser.add_argument("--sortsyms", type=str)
    parser.add_argument("--compareFuncs", action="store_true")
    parser.add_argument("--similar", type=int)
    parser.add_argument("--partial", action="store_true")
    
    args = parser.parse_args()
    
    if args.help:
        print_usage()
        return

    if args.partial:
        find_partial_shares()
        return

    if args.sortsyms is not None:
        map_files = [args.sortsyms]
        if args.sortsyms == "all":
            map_files = MapFileNames

        print()

        for map_name in map_files:
            sym_path = f"configs/USA/maps/sym.{map_name}.txt"
            sym_text = sort_sym_by_address(read_file(sym_path))
            sym_text += "\n" # end file with newline
            with open(sym_path, "w", encoding="utf-8") as f:
                f.write(sym_text)
            print(f"Updated {sym_path}.")
        return

    elif args.similar is not None:
        if args.map1 is None:
            print_usage()
            return

        find_similar_functions(args.map1, args.similar)
        return

    elif args.compareFuncs:
        if args.map1 is None:
            print("--compareFuncs: func1 path not specified!\n")
        elif args.map2 is None:
            print("--compareFuncs: func2 path not specified!\n")

        if args.map1 is None or args.map2 is None:
            print_usage()
            return

        name_file1 = os.path.basename(args.map1)
        name_file2 = os.path.basename(args.map2)
        funcname_file1 = os.path.splitext(name_file1)[0]
        funcname_file2 = os.path.splitext(name_file2)[0]

        func1 = clean_file(read_file(args.map1), funcname_file1)
        func2 = clean_file(read_file(args.map2), funcname_file2)
        distance = Levenshtein.distance(func1, func2)
        print(f"Func distance: {distance}")
        if distance != 0:
            with open("func1.clean.txt", "w", encoding="utf-8") as f:
                f.write(func1)
            with open("func2.clean.txt", "w", encoding="utf-8") as f:
                f.write(func2)
            print("Wrote clean funcs to func1.clean.txt / func2.clean.txt")
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
            for map_name in MapFileNames:
                if map_name != args.map1:
                    find_equal_asm_files(searchType, args.map1, map_name, 0, args.update, args.update, args.when)
        else:
            find_equal_asm_files(searchType, args.map1, args.map2, 0, args.update, args.update, args.when)
            
if __name__ == "__main__":
    main()
