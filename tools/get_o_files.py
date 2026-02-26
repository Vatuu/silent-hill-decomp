import yaml
import os
import sys

def get_o_target(yaml_file, release, compile_asm_tu):
    current_dir = os.getcwd()
    yaml_path = os.path.join(current_dir, f"configs/{release}/{yaml_file}.yaml")
    
    with open(yaml_path, 'r') as file:
        data = yaml.safe_load(file)
        target_path = data.get('options').get('target_path', 'target_path not found')
        build_path = data.get('options').get('build_path')
        src_path      = f"{build_path}/{data.get('options').get('src_path')}"
        asm_base_path = data.get('options').get('asm_path')
        asm_path      = f"{build_path}/{asm_base_path}"
        splits_paths = []
        splits_asm   = []
        splits_c     = []
        splits_bin   = []
        
        for segment in data.get('segments'):
            if len(segment) != 1:
                name = segment["name"]
                extension = segment["type"]
                match extension:
                    case "code":
                        for splits in segment.get('subsegments'):
                            try:
                                match splits[1]:
                                    case "rodata" | "data" | "sdata" | "bss" | "sbss":
                                        if len(splits) == 3:
                                            splits_asm.append(f"{asm_path}/data/{splits[2]}.{splits[1]}.s.o")
                                        else:
                                            splits_asm.append(f"{asm_path}/data/{hex(splits[0])[2:].upper()}.{splits[1]}.s.o")
                                    case "c":
                                        splits_c.append(f"{src_path}/{splits[2]}.c.o")
                                        asm_tu = f"{asm_base_path}/{splits[2]}.s"
                                        if compile_asm_tu == "1" and os.path.exists(asm_tu):
                                            splits_asm.append(f"{build_path}/{asm_tu}.o")
                                    case "asm":
                                        splits_asm.append(f"{asm_path}/{splits[2]}.s.o")
                                    case ".rodata" | ".data" | ".sdata" | ".bss" | ".sbss" | "pad" | "lib" | ".rdata" | "o":
                                        """
                                        Hi, I don't have any SH fun fact for today.
                                        """
                            except:
                                """
                                Did you know that Silent Hill: Downpour was going to feature
                                a similar psychological profile to Silent Hill: Shattered Memories.
                                """
                    case "header":
                        splits_asm.append(f"{asm_path}/{name}.s.o")
                    case _:
                        splits_bin.append(f"{asm_path}/{name}.{extension}.o")
        
        splits_paths.extend(splits_asm)
        splits_paths.extend(splits_c)
        splits_paths.extend(splits_bin)
        
        return splits_paths

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 tools/get_o_files.py <config_file>.yaml <release> <compile_asm_tu>")
        sys.exit(1)
    
    yaml_file      = sys.argv[1]
    release        = sys.argv[2]
    if len(sys.argv) == 3:
        compile_asm_tu = 0
    else:
        compile_asm_tu = sys.argv[3]
    target_path = get_o_target(yaml_file, release, compile_asm_tu)
    print(*target_path)
