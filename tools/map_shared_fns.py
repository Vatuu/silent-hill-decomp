# Compares ASM of funcs in first map folder against funcs in second map, and prints matching filenames.
# Funcs are compared by removing any block-comments and data/func refs, and then checking Levenshtein distance.
# Any with distance = 0 will then be printed.
#
# Usage:
#   python tools/map_shared_fns.py [--matchings] [--nonmatchings] [--replace] first_map_name second_map_name
#     --matchings: only compare first map `matchings` against second map nonmatchings
#     --nonmatchings: only compare first map `nonmatchings` against second map nonmatchings
#     --replace: replaces INCLUDE_ASM lines inside second map .c with #include, when sharedFuncs are found
#
# If a matching func is found which is named as sharedFunc_XXXXXXXX_0_s00 in first-map folder (where 0_s00 is map number, eg. map0_s00)
# It'll also print out lines to add in sym.txt file and #includes to add in .c file
# If --replace flag is provided it'll try replacing the INCLUDE_ASM line in second maps .c with #include lines.
# (more info at https://github.com/Vatuu/silent-hill-decomp/issues/74#issuecomment-2816256817)

import os
import re
import Levenshtein

def count_lines_in_file(file_path):
    try:
        with open(file_path, 'r') as file:
            return sum(1 for _ in file)
    except Exception as e:
        print(f"Error reading {file_path}: {e}")
        return -1

def read_and_clean_file(file_path):
    try:
        with open(file_path, 'r') as file:
            content = file.read()
            # Remove /* blockquote comments */
            content = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
            # Remove func_[8 chars], D_[8 chars], L[8 chars], jtbl_[8 chars]
            content = re.sub(r'func_[a-fA-F0-9]{8}', 'func', content)
            content = re.sub(r'D_[a-fA-F0-9]{8}', 'D', content)
            content = re.sub(r'L[a-fA-F0-9]{8}', 'L', content)
            content = re.sub(r'jtbl_[a-fA-F0-9]{8}', 'jtbl', content)
            # Remove sharedFunc_[8 chars]_[digit]_[3 chars]
            content = re.sub(r'sharedFunc_[a-fA-F0-9]{8}_[0-9]{1}_[a-zA-Z0-9]{3}', 'func', content)
            return content
    except Exception as e:
        print(f"Error reading {file_path}: {e}")
        return None

def find_equal_asm_files(searchType, map1, map2, maxdistance, replaceIncludeAsm):
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
    sharedFuncSymbols = ""

    # include lines to add to .c file
    includeLines = ""

    # search-replace changes to make inside .c file, if --replace is specified
    replacements = {}
    
    if matched_files:
        print(f"Matches for distance <= {maxdistance}:")
        for file1, file2, count in matched_files:
            
            # Read and clean the contents
            content1 = read_and_clean_file(file1)
            content2 = read_and_clean_file(file2)
            
            if content1 is not None and content2 is not None:
                # Compute Levenshtein distance
                distance = Levenshtein.distance(content1, content2)
                if distance <= maxdistance:
                    relative_file1 = os.path.relpath(file1, map1_asm_path)
                    relative_file2 = os.path.relpath(file2, map2_asm_path)
                    name_file1 = os.path.basename(file1)
                    name_file2 = os.path.basename(file2)

                    print(f"  {relative_file1} and {relative_file2}: {distance}")
                    
                    # If first dir func is named sharedFunc, print symbol names/includes for user to add to second map
                    if "sharedFunc" in name_file1:
                        funcName = name_file1.split(".")[0]
                        addr = name_file2.split("_")[1]
                        addr = addr.split(".")[0]
                        sharedFuncSymbols += f"\n{funcName} = 0x{addr}; // type:func"

                        include_key = f'INCLUDE_ASM("asm/maps/{map2}/nonmatchings/{map2}", func_{addr});'
                        include_value = f'#include "maps/shared/{funcName}.h" // 0x{addr}'
                        includeLines += "\n" + include_value
                        replacements[include_key] = include_value

        if sharedFuncSymbols:
            print(f"\nsym.{map2}.txt adds:")
            print(sharedFuncSymbols)

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
    else:
        print("\nNo matching files found.")

if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(
        description="Find matching functions between two map folders."
    )
    
    parser.add_argument("map1", type=str, help="First map folder")
    parser.add_argument("map2", type=str, help="Second map folder")

    parser.add_argument("--nonmatchings", action="store_true", help="Check nonmatchings in first folder against nonmatchings in second")
    parser.add_argument("--matchings", action="store_true", help="Check matchings in first folder against nonmatchings in second")
    parser.add_argument("--replace", action="store_true", help="Replaces INCLUDE_ASM lines inside second map .c with #include, when sharedFuncs are found")
    args = parser.parse_args()

    searchType = "all"
    if args.matchings:
        searchType = "matchings"
    if args.nonmatchings:
        searchType = "nonmatchings"

    find_equal_asm_files(searchType, args.map1, args.map2, 0, args.replace)
