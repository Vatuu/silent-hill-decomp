# Configuration

BUILD_EXE      ?= 1
BUILD_ENGINE   ?= 1
BUILD_SCREENS  ?= 1
BUILD_MAPS     ?= 1
CHECKSUM       ?= 1
NON_MATCHING   ?= 0
SKIP_ASM       ?= 0

# Names and Paths
#
# Versions supported
#
# Retail:
# USA

GAME_VERSION = USA

ifeq ($(GAME_VERSION), USA)

# Version - Retail NTSC (1.1)

GAME_NAME        := SLUS-00707
GAME_VERSION_DIR := USA
GAME_FILE_EXE    := SLUS_007.07
GAME_FILE_SILENT := SILENT.
GAME_FILE_HILL   := HILL.

endif

ROM_DIR      := rom
CONFIG_DIR   := configs/$(GAME_VERSION_DIR)
LINKER_DIR   := linkers
IMAGE_DIR    := $(ROM_DIR)/image
BUILD_DIR    := build
OUT_DIR      := $(BUILD_DIR)/out
TOOLS_DIR    := tools
OBJDIFF_DIR  := $(TOOLS_DIR)/objdiff
PERMUTER_DIR := permuter
ASSETS_DIR   := assets
ASM_DIR      := asm
C_DIR        := src
EXPECTED_DIR := expected

# Tools
# Note: CPP stands for `C Pre-Processor` not `C++`

CROSS   := mips-linux-gnu
AS      := $(CROSS)-as
LD      := $(CROSS)-ld
OBJCOPY := $(CROSS)-objcopy
OBJDUMP := $(CROSS)-objdump
CPP     := $(CROSS)-cpp
CC      := $(TOOLS_DIR)/gcc-2.8.1-psx/cc1
OBJDIFF := $(OBJDIFF_DIR)/objdiff

PYTHON          := python3
SPLAT           := $(PYTHON) -m splat split
MASPSX          := $(PYTHON) $(TOOLS_DIR)/maspsx/maspsx.py
DUMPSXISO       := $(TOOLS_DIR)/psxiso/dumpsxiso
MKPSXISO        := $(TOOLS_DIR)/psxiso/mkpsxiso
SILENT_ASSETS   := $(PYTHON) $(TOOLS_DIR)/silentassets/extract.py
INSERT_OVLS     := $(PYTHON) $(TOOLS_DIR)/silentassets/insertovl.py
GET_YAML_TARGET := $(PYTHON) $(TOOLS_DIR)/get_yaml_target.py
PREBUILD        := $(TOOLS_DIR)/prebuild.sh
POSTBUILD       := $(TOOLS_DIR)/postbuild.sh
COMPTEST        := $(TOOLS_DIR)/compilationTest.sh

# Flags
OPT_FLAGS           := -O2
ENDIAN              := -EL
INCLUDE_FLAGS       := -Iinclude -I $(BUILD_DIR) -Iinclude/psyq
DEFINE_FLAGS        := -D_LANGUAGE_C -DUSE_INCLUDE_ASM
CPP_FLAGS           := $(INCLUDE_FLAGS) $(DEFINE_FLAGS) -P -MMD -MP -undef -Wall -lang-c -nostdinc
LD_FLAGS            := $(ENDIAN) $(OPT_FLAGS) -nostdlib --no-check-sections
OBJCOPY_FLAGS       := -O binary
OBJDUMP_FLAGS       := --disassemble-all --reloc --disassemble-zeroes -Mreg-names=32
SPLAT_FLAGS         := --disassemble-all --make-full-disasm-for-code
DUMPSXISO_FLAGS     := -x "$(ROM_DIR)/$(GAME_VERSION)" -s "$(ROM_DIR)/$(GAME_VERSION)/layout.xml" "$(IMAGE_DIR)/$(GAME_NAME).bin"
MKPSXISO_FLAGS      := -y -q "$(ROM_DIR)/$(GAME_VERSION)/rebuild.xml"
SILENT_ASSETS_FLAGS := -exe "$(ROM_DIR)/$(GAME_VERSION)/$(GAME_FILE_EXE)" -fs "$(ROM_DIR)/$(GAME_VERSION)/$(GAME_FILE_SILENT)" -fh "$(ROM_DIR)/$(GAME_VERSION)/$(GAME_FILE_HILL)" "$(ASSETS_DIR)/$(GAME_VERSION)"
INSERT_OVLS_FLAGS   := -exe "$(ROM_DIR)/$(GAME_VERSION)/$(GAME_FILE_EXE)" -fs "$(ROM_DIR)/$(GAME_VERSION)/$(GAME_FILE_SILENT)" -ftb "$(ASSETS_DIR)/$(GAME_VERSION)/filetable.c.inc" -b $(OUT_DIR) -xml "$(ROM_DIR)/$(GAME_VERSION)/layout.xml" -o $(ROM_DIR)

# Targets that will run tools/prebuild.sh after splat has finished, before being built.
TARGET_PREBUILD  := main bodyprog screens/stream

# Targets that will run tools/postbuild.sh after being linked & extracted from ELF.
TARGET_POSTBUILD := bodyprog screens/stream

# Adjusts compiler and assembler flags based on source file location.
# - Files under main executable paths use -G8; overlay files use -G0.
# - Enables `--expand-div` for certain `libsd` sources which require it (others can't build with it).
# - Adds overlay-specific compiler flags based on files directory (currently only per-map defines).
define FlagsSwitch
	$(if $(findstring /main/,$(1)), $(eval DL_FLAGS = -G8), $(eval DL_FLAGS = -G0))
	$(eval AS_FLAGS = $(ENDIAN) $(INCLUDE_FLAGS) $(OPT_FLAGS) $(DL_FLAGS) -march=r3000 -mtune=r3000 -no-pad-sections)
	$(eval CC_FLAGS = $(OPT_FLAGS) $(DL_FLAGS) -mips1 -mcpu=3000 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet)
	
	$(if $(or $(findstring smf_mid,$(1)), $(findstring smf_io,$(1)),), \
		$(eval MASPSX_FLAGS = --aspsx-version=2.77 --run-assembler --expand-div $(AS_FLAGS)), \
		$(eval MASPSX_FLAGS = --aspsx-version=2.77 --run-assembler $(AS_FLAGS)))

	$(eval _rel_path := $(patsubst build/src/maps/%,%,$(patsubst build/${asm}/maps/%,%,$(1))))
	$(eval _map_name := $(shell echo $(word 1, $(subst /, ,$(_rel_path))) | tr a-z A-Z))
	$(if $(and $(findstring MAP,$(_map_name)),$(findstring _S,$(_map_name))), \
		$(eval OVL_FLAGS := -D$(_map_name)), \
		$(eval OVL_FLAGS :=))
endef

ifeq ($(NON_MATCHING),1)
	CPP_FLAGS := $(CPP_FLAGS) -DNON_MATCHING
endif

ifeq ($(SKIP_ASM),1)
	CPP_FLAGS := $(CPP_FLAGS) -DSKIP_ASM
endif

# Utils

# Function to find matching .bin files for a target name.
find_bin_files = $(shell find $(ASM_DIR)/$(strip $1) -type f -path "*.bin" 2> /dev/null)

# Function to find matching .s files for a target name.
find_s_files = $(shell find $(ASM_DIR)/$(strip $1) -type f -path "*.s" -not -path "asm/*matchings*" 2> /dev/null)

# Function to find matching .c files for a target name.
find_c_files = $(shell find $(C_DIR)/$(strip $1) -type f -path "*.c" 2> /dev/null)

# Function to generate matching .o files for target name in build directory.
gen_o_files = $(addprefix $(BUILD_DIR)/, \
							$(patsubst %.s, %.s.o, $(call find_s_files, $1)) \
							$(patsubst %.c, %.c.o, $(call find_c_files, $1)) \
							$(patsubst %.bin, %.bin.o, $(call find_bin_files, $1)))

# Function to get path to .yaml file for given target.
get_yaml_path = $(addsuffix .yaml,$(addprefix $(CONFIG_DIR)/,$1))

# Function to get target output path for given target.
get_target_out = $(patsubst $(OUT_DIR)/$(GAME_VERSION)%,$(OUT_DIR)%,$(addprefix $(OUT_DIR)/,$(shell $(GET_YAML_TARGET) $(call get_yaml_path,$1))))

# Template definition for elf target.
# First parameter should be source target with folder (e.g. screens/credits).
# Second parameter should be end target (e.g. build/VIN/STF_ROLL.BIN).
# If we skip the ASM inclusion to determine progress, we will not be able to link. Skip linking, if so.

ifeq ($(SKIP_ASM),1)

define make_elf_target
$2: $2.elf

$2.elf: $(call gen_o_files, $1)
#endef make_elf_target
endef

#else SKIP_ASM
else

define make_elf_target

ifeq ($(GAME_VERSION), USA)

$2: $2.elf
	$(OBJCOPY) $(OBJCOPY_FLAGS) $$< $$@
ifneq (,$(filter $1,$(TARGET_POSTBUILD)))
	-$(POSTBUILD) $1
endif

$2.elf: $(call gen_o_files, $1)
	@mkdir -p $(dir $2)
	$(LD) $(LD_FLAGS) \
		-Map $2.map \
		-T $(LINKER_DIR)/$1.ld \
		-T $(LINKER_DIR)/$(filter-out ./,$(dir $1))undefined_syms_auto.$(notdir $1).txt \
		-T $(LINKER_DIR)/$(filter-out ./,$(dir $1))undefined_funcs_auto.$(notdir $1).txt \
		-T $(CONFIG_DIR)/lib_externs.ld \
		-o $$@

#else GAME_VERSION
else

$2: $2.elf
	$(OBJCOPY) $(OBJCOPY_FLAGS) $$< $$@

$2.elf: $(call gen_o_files, $1)
	@mkdir -p $(dir $2)
	$(LD) $(LD_FLAGS) \
		-Map $2.map \
		-T $(LINKER_DIR)/$1.ld \
		-T $(LINKER_DIR)/$(filter-out ./,$(dir $1))undefined_syms_auto.$(notdir $1).txt \
		-T $(LINKER_DIR)/$(filter-out ./,$(dir $1))undefined_funcs_auto.$(notdir $1).txt \
		-o $$@

#endif GAME_VERSION
endif

#endef make_elf_target
endef

#endif SKIP_ASM
endif

# Targets

TARGET_SCREENS_SRC_DIR := screens
TARGET_MAPS_SRC_DIR := maps

ifeq ($(EXE)$(ENG)$(BKO)$(CRE)$(OPT)$(SAV)$(FMV)$(M00)$(M01)$(M02)$(M10)$(M11)$(M12)$(M13)$(M14)$(M15)$(M16)$(M20)$(M21)$(M22)$(M23)$(M24)$(M30)$(M31)$(M32)$(M33)$(M34)$(M35)$(M36)$(M40)$(M41)$(M42)$(M43)$(M44)$(M45)$(M46)$(M50)$(M51)$(M52)$(M53)$(M60)$(M61)$(M62)$(M63)$(M64)$(M65)$(M70)$(M71)$(M72)$(M73)$(M0X)$(M1X)$(M2X)$(M3X)$(M4X)$(M5X)$(M6X)$(M7X)$(SCR)$(STR)$(MAP),)

ifeq ($(BUILD_EXE), 1)

TARGET_MAIN := main

#endif BUILD_EXE
endif

ifeq ($(BUILD_ENGINE), 1)

TARGET_BODYPROG := bodyprog

#endif BUILD_ENGINE
endif

ifeq ($(BUILD_SCREENS), 1)

TARGET_SCREENS := b_konami credits options saveload stream
TARGET_SCREENS := $(addprefix $(TARGET_SCREENS_SRC_DIR)/,$(TARGET_SCREENS))

#endif BUILD_SCREENS
endif

ifeq ($(BUILD_MAPS), 1)

TARGET_MAPS := map0_s00 map0_s01 map0_s02 \
                map1_s00 map1_s01 map1_s02 map1_s03 map1_s04 map1_s05 map1_s06 \
                map2_s00 map2_s01 map2_s02 map2_s03 map2_s04 \
                map3_s00 map3_s01 map3_s02 map3_s03 map3_s04 map3_s05 map3_s06 \
                map4_s00 map4_s01 map4_s02 map4_s03 map4_s04 map4_s05 map4_s06 \
                map5_s00 map5_s01 map5_s02 map5_s03 \
                map6_s00 map6_s01 map6_s02 map6_s03 map6_s04 map6_s05 \
                map7_s00 map7_s01 map7_s02 map7_s03

TARGET_MAPS := $(addprefix $(TARGET_MAPS_SRC_DIR)/,$(TARGET_MAPS))

#endif BUILD_MAPS
endif

TARGET_IN  := $(TARGET_MAIN) $(TARGET_BODYPROG) $(TARGET_SCREENS) $(TARGET_MAPS)

else
# Specific overlay compilation/generation


TARGET_MAPS := map0_s00 map0_s01 map0_s02 \
                map1_s00 map1_s01 map1_s02 map1_s03 map1_s04 map1_s05 map1_s06 \
                map2_s00 map2_s01 map2_s02 map2_s03 map2_s04 \
                map3_s00 map3_s01 map3_s02 map3_s03 map3_s04 map3_s05 map3_s06 \
                map4_s00 map4_s01 map4_s02 map4_s03 map4_s04 map4_s05 map4_s06 \
                map5_s00 map5_s01 map5_s02 map5_s03 \
                map6_s00 map6_s01 map6_s02 map6_s03 map6_s04 map6_s05 \
                map7_s00 map7_s01 map7_s02 map7_s03

TARGET_MAPS := $(addprefix $(TARGET_MAPS_SRC_DIR)/,$(TARGET_MAPS))

TARGET_EXE_$(EXE)             := main
TARGET_ENG_$(ENG)             := bodyprog
TARGET_BKO_$(BKO)$(SCR)       := $(TARGET_SCREENS_SRC_DIR)/b_konami
TARGET_CRE_$(CRE)$(SCR)       := $(TARGET_SCREENS_SRC_DIR)/credits
TARGET_OPT_$(OPT)$(SCR)       := $(TARGET_SCREENS_SRC_DIR)/options
TARGET_SAV_$(SAV)$(SCR)       := $(TARGET_SCREENS_SRC_DIR)/saveload
TARGET_FMV_$(FMV)$(STR)$(SCR) := $(TARGET_SCREENS_SRC_DIR)/stream
TARGET_MAP_$(MAP)             := TARGET_MAPS
TARGET_M00_$(M00)$(M0X)       := $(TARGET_MAPS_SRC_DIR)/map0_s00
TARGET_M01_$(M01)$(M0X)       := $(TARGET_MAPS_SRC_DIR)/map0_s01
TARGET_M02_$(M02)$(M0X)       := $(TARGET_MAPS_SRC_DIR)/map0_s02
TARGET_M10_$(M10)$(M1X)       := $(TARGET_MAPS_SRC_DIR)/map1_s00
TARGET_M11_$(M11)$(M1X)       := $(TARGET_MAPS_SRC_DIR)/map1_s01
TARGET_M12_$(M12)$(M1X)       := $(TARGET_MAPS_SRC_DIR)/map1_s02
TARGET_M13_$(M13)$(M1X)       := $(TARGET_MAPS_SRC_DIR)/map1_s03
TARGET_M14_$(M14)$(M1X)       := $(TARGET_MAPS_SRC_DIR)/map1_s04
TARGET_M15_$(M15)$(M1X)       := $(TARGET_MAPS_SRC_DIR)/map1_s05
TARGET_M16_$(M16)$(M1X)       := $(TARGET_MAPS_SRC_DIR)/map1_s06
TARGET_M20_$(M20)$(M2X)       := $(TARGET_MAPS_SRC_DIR)/map2_s00
TARGET_M21_$(M21)$(M2X)       := $(TARGET_MAPS_SRC_DIR)/map2_s01
TARGET_M22_$(M22)$(M2X)       := $(TARGET_MAPS_SRC_DIR)/map2_s02
TARGET_M23_$(M23)$(M2X)       := $(TARGET_MAPS_SRC_DIR)/map2_s03
TARGET_M24_$(M24)$(M2X)       := $(TARGET_MAPS_SRC_DIR)/map2_s04
TARGET_M30_$(M30)$(M3X)       := $(TARGET_MAPS_SRC_DIR)/map3_s00
TARGET_M31_$(M31)$(M3X)       := $(TARGET_MAPS_SRC_DIR)/map3_s01
TARGET_M32_$(M32)$(M3X)       := $(TARGET_MAPS_SRC_DIR)/map3_s02
TARGET_M33_$(M33)$(M3X)       := $(TARGET_MAPS_SRC_DIR)/map3_s03
TARGET_M34_$(M34)$(M3X)       := $(TARGET_MAPS_SRC_DIR)/map3_s04
TARGET_M35_$(M35)$(M3X)       := $(TARGET_MAPS_SRC_DIR)/map3_s05
TARGET_M36_$(M36)$(M3X)       := $(TARGET_MAPS_SRC_DIR)/map3_s06
TARGET_M40_$(M40)$(M4X)       := $(TARGET_MAPS_SRC_DIR)/map4_s00
TARGET_M41_$(M41)$(M4X)       := $(TARGET_MAPS_SRC_DIR)/map4_s01
TARGET_M42_$(M42)$(M4X)       := $(TARGET_MAPS_SRC_DIR)/map4_s02
TARGET_M43_$(M43)$(M4X)       := $(TARGET_MAPS_SRC_DIR)/map4_s03
TARGET_M44_$(M44)$(M4X)       := $(TARGET_MAPS_SRC_DIR)/map4_s04
TARGET_M45_$(M45)$(M4X)       := $(TARGET_MAPS_SRC_DIR)/map4_s05
TARGET_M46_$(M46)$(M4X)       := $(TARGET_MAPS_SRC_DIR)/map4_s06
TARGET_M50_$(M50)$(M5X)       := $(TARGET_MAPS_SRC_DIR)/map5_s00
TARGET_M51_$(M51)$(M5X)       := $(TARGET_MAPS_SRC_DIR)/map5_s01
TARGET_M52_$(M52)$(M5X)       := $(TARGET_MAPS_SRC_DIR)/map5_s02
TARGET_M53_$(M53)$(M5X)       := $(TARGET_MAPS_SRC_DIR)/map5_s03
TARGET_M60_$(M60)$(M6X)       := $(TARGET_MAPS_SRC_DIR)/map6_s00
TARGET_M61_$(M61)$(M6X)       := $(TARGET_MAPS_SRC_DIR)/map6_s01
TARGET_M62_$(M62)$(M6X)       := $(TARGET_MAPS_SRC_DIR)/map6_s02
TARGET_M63_$(M63)$(M6X)       := $(TARGET_MAPS_SRC_DIR)/map6_s03
TARGET_M64_$(M64)$(M6X)       := $(TARGET_MAPS_SRC_DIR)/map6_s04
TARGET_M65_$(M65)$(M6X)       := $(TARGET_MAPS_SRC_DIR)/map6_s05
TARGET_M70_$(M70)$(M7X)       := $(TARGET_MAPS_SRC_DIR)/map7_s00
TARGET_M71_$(M71)$(M7X)       := $(TARGET_MAPS_SRC_DIR)/map7_s01
TARGET_M72_$(M72)$(M7X)       := $(TARGET_MAPS_SRC_DIR)/map7_s02
TARGET_M73_$(M73)$(M7X)       := $(TARGET_MAPS_SRC_DIR)/map7_s03

TARGET_IN := $(TARGET_EXE_1) $(TARGET_ENG_1) $(TARGET_BKO_1) $(TARGET_CRE_1) $(TARGET_OPT_1) $(TARGET_SAV_1) $(TARGET_FMV_1) $(TARGET_M00_1) $(TARGET_M01_1) $(TARGET_M02_1) $(TARGET_M10_1) $(TARGET_M11_1) $(TARGET_M12_1) $(TARGET_M13_1) $(TARGET_M14_1) $(TARGET_M15_1) $(TARGET_M16_1) $(TARGET_M20_1) $(TARGET_M21_1) $(TARGET_M22_1) $(TARGET_M23_1) $(TARGET_M24_1) $(TARGET_M30_1) $(TARGET_M31_1) $(TARGET_M32_1) $(TARGET_M33_1) $(TARGET_M34_1) $(TARGET_M35_1) $(TARGET_M36_1) $(TARGET_M40_1) $(TARGET_M41_1) $(TARGET_M42_1) $(TARGET_M43_1) $(TARGET_M44_1) $(TARGET_M45_1) $(TARGET_M46_1) $(TARGET_M50_1) $(TARGET_M51_1) $(TARGET_M52_1) $(TARGET_M53_1) $(TARGET_M60_1) $(TARGET_M61_1) $(TARGET_M62_1) $(TARGET_M63_1) $(TARGET_M64_1) $(TARGET_M65_1) $(TARGET_M70_1) $(TARGET_M71_1) $(TARGET_M72_1) $(TARGET_M73_1) $(TARGET_MAP_1)

endif

# Source Definitions

TARGET_OUT := $(foreach target,$(TARGET_IN),$(call get_target_out,$(target)))

CONFIG_FILES := $(foreach target,$(TARGET_IN),$(call get_yaml_path,$(target)))
LD_FILES     := $(addsuffix .ld,$(addprefix $(LINKER_DIR)/,$(TARGET_IN)))

# Recursively include any .d dependency files from previous builds.
# Allowing Make to rebuild targets when any included headers/sources change.
-include $(shell [ -d $(BUILD_DIR) ] && find $(BUILD_DIR) -name '*.d' || true)

# Rules

# Rules - Build (Normal/Matching)

default: build

build: $(TARGET_OUT) checksum

reset-build:
	rm -rf $(BUILD_DIR)/src
	rm -rf $(OUT_DIR)
	$(MAKE) build $(TARGET_OUT) checksum

clean-build: reset
	$(MAKE) generate
	$(MAKE) build

generate: $(LD_FILES)

# Rules - Build (Objdiff/Progress)

objdiff-config:
	rm -rf $(EXPECTED_DIR)
	$(MAKE) regenerate
	$(MAKE) NON_MATCHING=1 SKIP_ASM=1 build
	mkdir -p $(EXPECTED_DIR)
	mv $(BUILD_DIR)/asm $(EXPECTED_DIR)/asm
	$(PYTHON) $(OBJDIFF_DIR)/objdiff_generate.py $(OBJDIFF_DIR)/config.yaml

report:
	$(MAKE) BUILD_EXE=1 BUILD_ENGINE=1 BUILD_SCREENS=1 BUILD_MAPS=1 objdiff-config
	$(OBJDIFF) report generate > $(BUILD_DIR)/progress.json

progress:
	$(MAKE) NON_MATCHING=1 SKIP_ASM=1 build

reset-progress:
	rm -rf $(BUILD_DIR)/src
	rm -rf $(OUT_DIR)
	$(MAKE) NON_MATCHING=1 SKIP_ASM=1 build $(TARGET_OUT)

# Rules - Rom handling (Extraction/Insertion)
# TODO: Allow to insert any files to the game Files
# At the moment only overlays have been handled

setup: reset
	rm -rf $(EXPECTED_DIR)
	$(MAKE) extract
	$(MAKE) generate

insert-ovl:
	$(INSERT_OVLS) $(INSERT_OVLS_FLAGS)
	$(MKPSXISO) $(MKPSXISO_FLAGS)

extract:
	rm -rf "$(ASSETS_DIR)/$(GAME_VERSION)"
	$(DUMPSXISO) $(DUMPSXISO_FLAGS)
	$(SILENT_ASSETS) $(SILENT_ASSETS_FLAGS)

# Rules - Cleaning

clean-rom:
	find $(ROM_DIR) -maxdepth 1 -type f -delete
	find $(ROM_DIR)/$(GAME_VERSION_DIR) -maxdepth 1 -type f -delete

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(PERMUTER_DIR)

reset: clean
	rm -rf $(ASM_DIR)
	rm -rf $(LINKER_DIR)

# Rules - Misc.

regenerate: reset
	$(MAKE) generate

compilation-test:
	$(COMPTEST)

checksum: $(TARGET_OUT)
ifeq ($(CHECKSUM),1)
ifeq ($(SKIP_ASM),0)
	@sha256sum --ignore-missing --check "$(CONFIG_DIR)/checksum.sha"
endif
endif

# Recipes

# .elf targets
# Generate .elf target for each target from TARGET_IN.
$(foreach target,$(TARGET_IN),$(eval $(call make_elf_target,$(target),$(call get_target_out,$(target)))))

# Generate objects.
# (Running make with MAKE_COMPILE_LOG=1 will create a compile.log that can be passed to tools/create_compile_commands.py)

$(BUILD_DIR)/%.i: %.c
	@mkdir -p $(dir $@)
	$(call FlagsSwitch, $@)
ifeq ($(MAKE_COMPILE_LOG),1)
	@echo "$(CPP) -P -MMD -MP -MT $@ -MF $@.d $(CPP_FLAGS) $(OVL_FLAGS) -o $@ $<" >> compile.log
endif
	$(CPP) -P -MMD -MP -MT $@ -MF $@.d $(CPP_FLAGS) $(OVL_FLAGS) -o $@ $<

$(BUILD_DIR)/%.sjis.i: $(BUILD_DIR)/%.i
	iconv -f UTF-8 -t SHIFT-JIS $< -o $@

$(BUILD_DIR)/%.c.s: $(BUILD_DIR)/%.sjis.i
	@mkdir -p $(dir $@)
	$(call FlagsSwitch, $@)
	$(CC) $(CC_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.o: $(BUILD_DIR)/%.c.s
	@mkdir -p $(dir $@)
	$(call FlagsSwitch, $@)
	$(MASPSX) $(MASPSX_FLAGS) -o $@ $<

$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(call FlagsSwitch, $@)
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) -r -b binary -o $@ $<

# Split .yaml.
$(LINKER_DIR)/%.ld: $(CONFIG_DIR)/%.yaml
	@mkdir -p $(dir $@)
	$(SPLAT) $(SPLAT_FLAGS) $<
	$(if $(filter $*,$(TARGET_PREBUILD)),@-$(PREBUILD) $*,@true)

### Settings
.SECONDARY:
.PHONY: clean default
SHELL = /bin/bash -e -o pipefail
