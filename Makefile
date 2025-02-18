# Configuration

BUILD_OVERLAYS ?= 1
BUILD_SCREENS  ?= 0
BUILD_MAPS     ?= 0
NON_MATCHING   ?= 0

# Names and Paths

GAME_NAME := SLUS-00707

ROM_DIR      := rom
CONFIG_DIR   := configs
LINKER_DIR   := linkers
IMAGE_DIR    := $(ROM_DIR)/image
BUILD_DIR    := build
TOOLS_DIR    := tools
PERMUTER_DIR := permuter
ASSETS_DIR   := assets
ASM_DIR      := asm
C_DIR        := src

# Tools

CROSS   := mips-linux-gnu
AS      := $(CROSS)-as
LD      := $(CROSS)-ld
OBJCOPY := $(CROSS)-objcopy
OBJDUMP := $(CROSS)-objdump
CPP     := $(CROSS)-cpp
CC      := $(TOOLS_DIR)/gcc-2.8.1-psx/cc1

PYTHON          := python3
SPLAT           := $(PYTHON) -m splat split
MASPSX          := $(PYTHON) $(TOOLS_DIR)/maspsx/maspsx.py
DUMPSXISO       := $(TOOLS_DIR)/psxiso/dumpsxiso
SILENT_ASSETS   := $(PYTHON) $(TOOLS_DIR)/silentassets/extract.py
GET_YAML_TARGET := $(PYTHON) $(TOOLS_DIR)/get_yaml_target.py

# Flags

OPT_FLAGS           := -O2
DL_FLAGS            := -G8
ENDIAN              := -EL
INCLUDE_FLAGS       := -Iinclude -I $(BUILD_DIR) -Iinclude/psyq
DEFINE_FLAGS        := -D_LANGUAGE_C -DUSE_INCLUDE_ASM
AS_FLAGS            := $(ENDIAN) $(INCLUDE_FLAGS) $(OPT_FLAGS) $(DL_FLAGS) -march=r3000 -mtune=r3000 -no-pad-sections
CC_FLAGS            := $(OPT_FLAGS) $(DL_FLAGS) -mips1 -mcpu=3000 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet
CPP_FLAGS           := $(INCLUDE_FLAGS) $(DEFINE_FLAGS) -P -MMD -MP -undef -Wall -lang-c -nostdinc
LD_FLAGS            := $(ENDIAN) $(OPT_FLAGS) -nostdlib --no-check-sections
OBJCOPY_FLAGS       := -O binary
OBJDUMP_FLAGS       := --disassemble-all --reloc --disassemble-zeroes -Mreg-names=32
SPLAT_FLAGS         := --disassemble-all
MASPSX_FLAGS        := --aspsx-version=2.77 --run-assembler $(AS_FLAGS)
DUMPSXISO_FLAGS     := -x $(ROM_DIR) -s $(ROM_DIR)/layout.xml $(IMAGE_DIR)/$(GAME_NAME).bin
SILENT_ASSETS_FLAGS := -exe $(ROM_DIR)/SLUS_007.07 -fs $(ROM_DIR)/SILENT. -fh $(ROM_DIR)/HILL. $(ASSETS_DIR)

ifeq ($(NON_MATCHING),1)
	DEFINE_FLAGS := $(DEFINE_FLAGS) -DNON_MATCHING
endif

# Utils

# Function to find matching .s files for a target name.
find_s_files = $(shell find $(ASM_DIR)/$(strip $1) -type f -path "*.s" -not -path "asm/*matchings*" 2> /dev/null)

# Function to find matching .c files for a target name.
find_c_files = $(shell find $(C_DIR)/$(strip $1) -type f -path "*.c" 2> /dev/null)

# Function to generate matching .o files for target name in build directory.
gen_o_files = $(addprefix $(BUILD_DIR)/, \
							$(patsubst %.s, %.s.o, $(call find_s_files, $1)) \
							$(patsubst %.c, %.c.o, $(call find_c_files, $1)))

# Function to get path to yaml file for given target.
get_yaml_path = $(addsuffix .yaml,$(addprefix $(CONFIG_DIR)/,$1))

# Function to get the target output path for given target
get_target_out = $(addprefix $(BUILD_DIR)/,$(shell $(GET_YAML_TARGET) $(call get_yaml_path,$1)))

# Template definition for elf target.
# First parameter should be source target with folder (e.g. screens/credits).
# Second parameter should be end target (e.g. build/VIN/STF_ROLL.BIN).
define make_elf_target
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
endef

# Targets

TARGET_SCREENS_SRC_DIR := screens
TARGET_MAPS_SRC_DIR := maps

TARGET_MAIN := main

ifeq ($(BUILD_OVERLAYS), 1)

TARGET_BODYPROG := bodyprog
TARGET_STREAM   := stream

ifeq ($(BUILD_SCREENS), 1)

TARGET_SCREENS := b_konami credits options saveload
TARGET_SCREENS := $(addprefix $(TARGET_SCREENS_SRC_DIR)/,$(TARGET_SCREENS))

endif

ifeq ($(BUILD_MAPS), 1)

TARGET_MAPS				:= map0_s00 map0_s01 map0_s02 \
							map1_s00 map1_s01 map1_s02 map1_s03 map1_s04 map1_s05 map1_s06 \
							map2_s00 map2_s01 map2_s02 map2_s03 map2_s04 \
							map3_s00 map3_s01 map3_s02 map3_s03 map3_s04 map3_s05 map3_s06 \
							map4_s00 map4_s01 map4_s02 map4_s03 map4_s04 map4_s05 map4_s06 \
							map5_s00 map5_s01 map5_s02 map5_s03 \
							map6_s00 map6_s01 map6_s02 map6_s03 map6_s04 map6_s05 \
							map7_s00 map7_s01 map7_s02 map7_s03
TARGET_MAPS				:= $(addprefix $(TARGET_MAPS_SRC_DIR)/,$(TARGET_MAPS))

endif

TARGET_OVERLAYS			:= $(TARGET_BODYPROG) $(TARGET_STREAM) $(TARGET_SCREENS) $(TARGET_MAPS)

endif

# Source Definitions

TARGET_IN  := $(TARGET_MAIN) $(TARGET_OVERLAYS)
TARGET_OUT := $(foreach target,$(TARGET_IN),$(call get_target_out,$(target)))

CONFIG_FILES := $(foreach target,$(TARGET_IN),$(call get_yaml_path,$(target)))
LD_FILES     := $(addsuffix .ld,$(addprefix $(LINKER_DIR)/,$(TARGET_IN)))

# Rules

default: all

all: check

build: $(TARGET_OUT)

check: build
	@sha256sum --ignore-missing --check checksum.sha

expected: check
	# Copying build results into "expected" folder
	mkdir -p expected/build
	cp -r build/src expected/build/src
	cp -r build/asm expected/build/asm
	# Future function changes can be diffed via:
	#  python3 tools/asm-differ/diff.py -mwo --overlay bodyprog vcRetMaxTgtMvXzLen
	# To try and decompile a function with M2C:
	#  python3 tools/decompile.py vcRetMaxTgtMvXzLen

extract:
	$(DUMPSXISO) $(DUMPSXISO_FLAGS)
	$(SILENT_ASSETS) $(SILENT_ASSETS_FLAGS)

generate: $(LD_FILES)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(PERMUTER_DIR)

reset: clean
	rm -rf $(ASM_DIR)
	rm -rf $(LINKER_DIR)

clean-rom:
	find rom -maxdepth 1 -type f -delete

regenerate: reset
	$(MAKE) generate

# Recursive call to force order of operations.
setup: clean-rom
	$(MAKE) extract
	$(MAKE) regenerate

# Recipes

# elf targets
# for each target from TARGET_IN generate an .elf target
$(foreach target,$(TARGET_IN),$(eval $(call make_elf_target,$(target),$(call get_target_out,$(target)))))

# Generate objects
$(BUILD_DIR)/%.i: %.c
	@mkdir -p $(dir $@)
	$(CPP) -P -MMD -MP -MT $@ -MF $@.d $(CPP_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.s: $(BUILD_DIR)/%.i
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.o: $(BUILD_DIR)/%.c.s
	@mkdir -p $(dir $@)
	$(MASPSX) $(MASPSX_FLAGS) -o $@ $<
	$(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)

$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<

# Split yaml
$(LINKER_DIR)/%.ld: $(CONFIG_DIR)/%.yaml
	@mkdir -p $(dir $@)
	$(SPLAT) $(SPLAT_FLAGS) $<

### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
