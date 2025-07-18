# Configuration

BUILD_ENGINE   ?= 1
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
OBJDIFF_DIR  := $(TOOLS_DIR)/objdiff
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
DUMPSXISO_FLAGS     := -x $(ROM_DIR) -s $(ROM_DIR)/layout.xml $(IMAGE_DIR)/$(GAME_NAME).bin
MKPSXISO_FLAGS      := -y -q $(ROM_DIR)/shgame.xml
SILENT_ASSETS_FLAGS := -exe $(ROM_DIR)/SLUS_007.07 -fs $(ROM_DIR)/SILENT. -fh $(ROM_DIR)/HILL. $(ASSETS_DIR)
INSERT_OVLS_FLAGS   := -exe $(ROM_DIR)/SLUS_007.07 -fs $(ROM_DIR)/SILENT. -ftb $(ASSETS_DIR)/filetable.c.inc -b $(OUT_DIR) -xml $(ROM_DIR)/layout.xml -o $(ROM_DIR)

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
	$(eval CC_FLAGS = $(OPT_FLAGS) $(DL_FLAGS) -mips1 -mcpu=3000 -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet)
	
	$(if $(or $(findstring smf_mid,$(1)), $(findstring smf_io,$(1)),), \
		$(eval MASPSX_FLAGS = --aspsx-version=2.77 --run-assembler --expand-div $(AS_FLAGS)), \
		$(eval MASPSX_FLAGS = --aspsx-version=2.77 --run-assembler $(AS_FLAGS)))

	$(eval _rel_path := $(patsubst build/src/maps/%,%,$(patsubst build/asm/maps/%,%,$(1))))
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
endef

endif

# Targets

TARGET_SCREENS_SRC_DIR := screens
TARGET_MAPS_SRC_DIR := maps

TARGET_MAIN := main

ifeq ($(BUILD_ENGINE), 1)

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

TARGET_OVERLAYS			:= $(TARGET_BODYPROG) $(TARGET_SCREENS) $(TARGET_MAPS)

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
	@$(MAKE) NON_MATCHING=1 SKIP_ASM=1 expected
	@$(PYTHON) $(OBJDIFF_DIR)/objdiff_generate.py $(OBJDIFF_DIR)/config.yaml

report: objdiff-config
	@$(OBJDIFF) report generate > $(BUILD_DIR)/progress.json

check: build
	@sha256sum --ignore-missing --check checksum.sha

progress:
	$(MAKE) build NON_MATCHING=1 SKIP_ASM=1

expected: build
	mkdir -p $(EXPECTED_DIR)
	mv build/asm $(EXPECTED_DIR)/asm

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
	rm -rf $(ASM_DIR)
	rm -rf $(LINKER_DIR)
	$(MAKE) generate
	$(MAKE) check

clean-progress: clean
	rm -rf $(ASM_DIR)
	rm -rf $(LINKER_DIR)
	$(MAKE) generate
	$(MAKE) progress

compilation-test:
	$(COMPTEST)

compilation-test-sm:
	$(COMPTEST) --skip-maps

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
	-$(MASPSX) $(MASPSX_FLAGS) -o $@ $<
	-$(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)

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
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
