# Configuration

BUILD_OVERLAYS ?= 1
BUILD_SCREENS  ?= 1
BUILD_MAPS     ?= 1
NON_MATCHING   ?= 0
SKIP_ASM       ?= 0

# Names and Paths

GAME_NAME := SLUS-00707

ROM_DIR      := rom
CONFIG_DIR   := configs
LINKER_DIR   := linkers
IMAGE_DIR    := $(ROM_DIR)/image
BUILD_DIR    := build
OUT_DIR      := $(BUILD_DIR)/out
TOOLS_DIR    := tools
OBJDIFF_DIR	 := $(TOOLS_DIR)/objdiff
PERMUTER_DIR := permuter
ASSETS_DIR   := assets
ASM_DIR      := asm
C_DIR        := src
EXPECTED_DIR := expected

# Tools

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

# Flags
OPT_FLAGS           := -O2
ENDIAN              := -EL
INCLUDE_FLAGS       := -Iinclude -I $(BUILD_DIR) -Iinclude/psyq
DEFINE_FLAGS        := -D_LANGUAGE_C -DUSE_INCLUDE_ASM
CPP_FLAGS           := $(INCLUDE_FLAGS) $(DEFINE_FLAGS) -P -MMD -MP -undef -Wall -lang-c -nostdinc
LD_FLAGS            := $(ENDIAN) $(OPT_FLAGS) -nostdlib --no-check-sections
OBJCOPY_FLAGS       := -O binary
OBJDUMP_FLAGS       := --disassemble-all --reloc --disassemble-zeroes -Mreg-names=32
SPLAT_FLAGS         := --disassemble-all
DUMPSXISO_FLAGS     := -x $(ROM_DIR) -s $(ROM_DIR)/layout.xml $(IMAGE_DIR)/$(GAME_NAME).bin
MKPSXISO_FLAGS      := -y -q -o $(BUILD_DIR) $(ROM_DIR)/shgame.xml
SILENT_ASSETS_FLAGS := -exe $(ROM_DIR)/SLUS_007.07 -fs $(ROM_DIR)/SILENT. -fh $(ROM_DIR)/HILL. $(ASSETS_DIR)
INSERT_OVLS_FLAGS   := -exe $(ROM_DIR)/SLUS_007.07 -fs $(ROM_DIR)/SILENT. -ftb $(ASSETS_DIR)/filetable.c.inc -b $(OUT_DIR) -xml $(ROM_DIR)/layout.xml -o $(ROM_DIR)

# Main executable uses -G8 while overlays use -G0.
# This function redefines required parameters for compilation checking depending on whether a file's route is from main executable or an overlay.

define DL_FlagsSwitch
	$(if $(or $(filter MAIN,$(patsubst build/src/main/%,MAIN,$(1))), $(filter MAIN,$(patsubst build/asm/main/%,MAIN,$(1)))), $(eval DL_FLAGS = -G8), $(eval DL_FLAGS = -G0))
	$(eval AS_FLAGS = $(ENDIAN) $(INCLUDE_FLAGS) $(OPT_FLAGS) $(DL_FLAGS) -march=r3000 -mtune=r3000 -no-pad-sections)
	$(eval CC_FLAGS = $(OPT_FLAGS) $(DL_FLAGS) -mips1 -mcpu=3000 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet)
	$(eval MASPSX_FLAGS = --aspsx-version=2.77 --run-assembler $(AS_FLAGS))
endef

ifeq ($(NON_MATCHING),1)
	CPP_FLAGS := $(CPP_FLAGS) -DNON_MATCHING
endif

ifeq ($(SKIP_ASM),1)
	CPP_FLAGS := $(CPP_FLAGS) -DSKIP_ASM
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

# Function to get path to .yaml file for given target.
get_yaml_path = $(addsuffix .yaml,$(addprefix $(CONFIG_DIR)/,$1))

# Function to get target output path for given target.
get_target_out = $(addprefix $(OUT_DIR)/,$(shell $(GET_YAML_TARGET) $(call get_yaml_path,$1)))

# Template definition for elf target.
# First parameter should be source target with folder (e.g. screens/credits).
# Second parameter should be end target (e.g. build/VIN/STF_ROLL.BIN).
# If we skip the ASM inclusion to determine progress, we will not be able to link. Skip linking, if so.

ifeq ($(SKIP_ASM),1)

define make_elf_target
$2: $2.elf

$2.elf: $(call gen_o_files, $1)
endef

else

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

endif

# Targets

TARGET_SCREENS_SRC_DIR := screens
TARGET_MAPS_SRC_DIR := maps

TARGET_MAIN := main

ifeq ($(BUILD_OVERLAYS), 1)

TARGET_BODYPROG := bodyprog

endif

ifeq ($(BUILD_SCREENS), 1)

TARGET_SCREENS := b_konami credits options saveload stream
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

# Source Definitions

TARGET_IN  := $(TARGET_MAIN) $(TARGET_OVERLAYS)
TARGET_OUT := $(foreach target,$(TARGET_IN),$(call get_target_out,$(target)))

CONFIG_FILES := $(foreach target,$(TARGET_IN),$(call get_yaml_path,$(target)))
LD_FILES     := $(addsuffix .ld,$(addprefix $(LINKER_DIR)/,$(TARGET_IN)))

# Rules

default: all

all: build

build: $(TARGET_OUT)

objdiff-config: regenerate
	@$(MAKE) NON_MATCHING=0 SKIP_ASM=0 expected
	@$(MAKE) NON_MATCHING=1 SKIP_ASM=1 build
	@$(PYTHON) $(OBJDIFF_DIR)/objdiff_generate.py $(OBJDIFF_DIR)/config.yaml

report: objdiff-config
	@$(OBJDIFF) report generate > $(BUILD_DIR)/progress.json

check: build
	@sha256sum --ignore-missing --check checksum.sha

progress: NON_MATCHING=1 SKIP_ASM=1 build

expected: check
	mkdir -p $(EXPECTED_DIR)
	mv build/src $(EXPECTED_DIR)/src
	mv build/asm $(EXPECTED_DIR)/asm
	rm -rf $(BUILD_DIR)

iso:
	$(INSERT_OVLS) $(INSERT_OVLS_FLAGS)
	$(MKPSXISO) $(MKPSXISO_FLAGS)

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
	rm -rf $(EXPECTED_DIR)

clean-rom:
	find rom -maxdepth 1 -type f -delete

regenerate: reset
	$(MAKE) generate

setup: reset
	$(MAKE) extract
	$(MAKE) generate

clean-build: clean
	rm -rf $(LINKER_DIR)
	$(MAKE) generate
	$(MAKE) build

clean-check: clean
	rm -rf $(LINKER_DIR)
	$(MAKE) generate
	$(MAKE) check

clean-progress: regenerate
	$(MAKE) NON_MATCHING=1 SKIP_ASM=1 build

# Recipes

# .elf targets
# Generate .elf target for each target from TARGET_IN.
$(foreach target,$(TARGET_IN),$(eval $(call make_elf_target,$(target),$(call get_target_out,$(target)))))

# Generate objects.
$(BUILD_DIR)/%.i: %.c
	@mkdir -p $(dir $@)
	$(call DL_FlagsSwitch, $@)
	$(CPP) -P -MMD -MP -MT $@ -MF $@.d $(CPP_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.s: $(BUILD_DIR)/%.i
	@mkdir -p $(dir $@)
	$(call DL_FlagsSwitch, $@)
	$(CC) $(CC_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.o: $(BUILD_DIR)/%.c.s
	@mkdir -p $(dir $@)
	$(call DL_FlagsSwitch, $@)
	-$(MASPSX) $(MASPSX_FLAGS) -o $@ $<
	-$(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)

$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(call DL_FlagsSwitch, $@)
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<

# Split .yaml.
$(LINKER_DIR)/%.ld: $(CONFIG_DIR)/%.yaml
	@mkdir -p $(dir $@)
	$(SPLAT) $(SPLAT_FLAGS) $<

### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail