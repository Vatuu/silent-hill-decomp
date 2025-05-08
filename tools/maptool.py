import sys
import struct
from dataclasses import dataclass
from typing import List
import os

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

OFFSET_mapOverlayHeader = 4
OFFSET_charaUpdateFuncs = 0x194
OFFSET_charaGroupIds = 0x248
OFFSET_charaSpawns = 0x24C

MapBasePath = "assets/VIN/"

def charaName(i, includeNum: bool = True):
    charName = e_ShCharacterId[i] if i < len(e_ShCharacterId) else f"Chara_Unknown{i}"
    if includeNum:
        return f"{i:>2} {charName}"
    return charName

def q20_12(value):
    return round(value / 4096.0, 3)
    
def q4_12(value):
    return round(value / 4096.0 * 360, 3)

@dataclass
class CharaSpawn:
    posX: float
    posZ: float
    chara_type: int
    rot: int
    anim_unchanged_flag: int
    unk: int

@dataclass
class MapData:
    update_funcs: List[int]
    group_charas: List[int]
    chara_spawns: List[CharaSpawn]

def read_map_data(filepath: str) -> MapData:
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
        data = f.read(2)
        group = list(data)

        f.seek(OFFSET_mapOverlayHeader + OFFSET_charaSpawns)
        chara_spawns = []
        for i in range(32):
            data = f.read(12)
            posX, chara_type, rot, anim_flag, unk, posZ = struct.unpack("<i4bi", data)
                         
            # When chara_type is 0 chara ID is taken from the group section, group[0] if current spawn id is 15 or below, group[1] if 16 or above
            if chara_type == 0:
                chara_type = group[1] if i >= 16 else group[0]
            
            chara_spawns.append(
                CharaSpawn(q20_12(posX), q20_12(posZ), chara_type, q4_12(16 * rot), anim_flag, unk)
            )

        return MapData(update_funcs=update_funcs, group_charas=group, chara_spawns=chara_spawns)

def print_map_data(map_data: MapData):
    if map_data.update_funcs:
        print("charaUpdateFuncs_194:")
        for index, funcAddr in enumerate(map_data.update_funcs):
            if funcAddr != 0:
                print(f"  {charaName(index)} = 0x{funcAddr:08X}")
        print()

    if map_data.group_charas:
        print("charaGroupIds_248:")
        for index, charaId in enumerate(map_data.group_charas):
            group_str = " 0 - 15: " if index == 0 else "16 - 31: "
            print(f"  {group_str}{charaName(charaId)}")
        print()

    if map_data.chara_spawns:
        print("charaSpawns_24C:")
        for index, spawn in enumerate(map_data.chara_spawns):
            if spawn.anim_unchanged_flag != 0 or spawn.posX != 0 or spawn.posZ != 0 or spawn.rot != 0:

                # func_80037F24 only seems to count as valid if anim_unchanged_flag != 0   
                unused_text = "" if spawn.anim_unchanged_flag != 0 else " (flag == 0, slot unused?)"
                print(f"  [{index:>2}] {charaName(spawn.chara_type)} = "
                      f"({spawn.posX},{spawn.posZ}) rot {spawn.rot} "
                      f"flag 0x{spawn.anim_unchanged_flag:X} unk 0x{spawn.unk:X}{unused_text}")

def main():
    search_mode = False
    search_id = None
    input_file = None

    args = sys.argv[1:]

    if len(args) == 0:
        print(f"Usage: {sys.argv[0]} <input_map_file> or --search <chara_number>")
        print("  --search: scans maps in current folder for mention of chara_number")
        sys.exit(1)

    # Parse command-line arguments
    if args[0] == "--search":
        search_mode = True
        if len(args) < 2:
            print("Error: --search requires a chara ID argument.")
            sys.exit(1)
        try:
            search_id = int(args[1])
        except ValueError:
            print(f"Error: invalid chara ID '{args[1]}'")
            sys.exit(1)
    else:
        input_file = args[0]

    if search_mode:
        print(f"Searching for chara {charaName(search_id)}...\n")
        
        for filename in os.listdir(MapBasePath):
            if filename.lower().startswith("map") and filename.lower().endswith(".bin"):  # Only process .bin files
                map_data = read_map_data(filename)
                if map_data is None:
                    continue
                    
                # Check if any spawns/updatefuncs/group are setup for this chara ID
                foundIn = ""
                for index, funcAddr in enumerate(map_data.update_funcs):
                    if index == search_id and funcAddr != 0:
                        foundIn += f"updateFuncs(0x{funcAddr:08X}) "
                        break
                for charaId in map_data.group_charas:
                    if charaId == search_id:
                        foundIn += "charaGroupIds "
                        break
                for spawn in map_data.chara_spawns:
                    if spawn.chara_type == search_id:
                        foundIn += "charaSpawns "
                        break
                if foundIn:
                    print(f"Found {charaName(search_id, False)} in {filename} - {foundIn}")

    elif input_file:
        if not input_file.endswith(".bin") and not input_file.endswith(".BIN"):
            input_file += ".bin"
        print(f"Reading {input_file.upper()}\n")
        map_data = read_map_data(input_file)
        print_map_data(map_data)
        
if __name__ == "__main__":
    main()
