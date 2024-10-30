# Configuration

BUILD_OVERLAYS 		?= 1
BUILD_MAPS			?= 0

# Names and Paths

GAME_NAME				:= SLUS-00707

ROM_DIR					:= rom
CONFIG_DIR				:= configs
LINKER_DIR	       		:= linkers
IMAGE_DIR				:= $(ROM_DIR)/image
BUILD_DIR       		:= build
TOOLS_DIR       		:= tools
PERMUTER_DIR       		:= permuter
ASSETS_DIR				:= assets
ASM_DIR					:= asm
C_DIR					:= src

# Targets

TARGET_MAIN_NAME		:= main
TARGET_MAIN_SRC			:= main
TARGET_MAIN 			:= $(BUILD_DIR)/SLUS_007.07

ifeq ($(BUILD_OVERLAYS), 1)

TARGET_BODYPROG_NAME	:= bodyprog
TARGET_BODYPROG_SRC		:= bodyprog
TARGET_BODYPROG			:= $(BUILD_DIR)/1ST/BODYPROG.BIN

TARGET_B_KONAMI_NAME	:= b_konami
TARGET_B_KONAMI_SRC		:= b_konami
TARGET_B_KONAMI			:= $(BUILD_DIR)/1ST/B_KONAMI.BIN

TARGET_1ST				:= $(TARGET_BODYPROG) $(TARGET_B_KONAMI)
TARGET_1ST_NAMES		:= $(TARGET_BODYPROG_NAME) $(TARGET_B_KONAMI_NAME)

TARGET_STREAM_NAME		:= stream
TARGET_STREAM_SRC		:= stream
TARGET_STREAM			:= $(BUILD_DIR)/VIN/STREAM.BIN

TARGET_CREDITS_NAME		:= credits
TARGET_CREDITS_DIR		:= screens
TARGET_CREDITS_SRC		:= $(TARGET_CREDITS_DIR)/$(TARGET_CREDITS_NAME)
TARGET_CREDITS			:= $(BUILD_DIR)/VIN/STF_ROLL.BIN

TARGET_OPTIONS_NAME		:= options
TARGET_OPTIONS_DIR		:= screens
TARGET_OPTIONS_SRC		:= $(TARGET_OPTIONS_DIR)/$(TARGET_OPTIONS_NAME)
TARGET_OPTIONS			:= $(BUILD_DIR)/VIN/OPTION.BIN

TARGET_SAVELOAD_NAME	:= saveload
TARGET_SAVELOAD_DIR		:= screens
TARGET_SAVELOAD_SRC		:= $(TARGET_SAVELOAD_DIR)/$(TARGET_SAVELOAD_NAME)
TARGET_SAVELOAD			:= $(BUILD_DIR)/VIN/SAVELOAD.BIN

ifeq ($(BUILD_MAPS), 1)

TARGET_MAP0_S00_BASE	:= map0_s00
TARGET_MAP0_S00_NAME	:= maps/$(TARGET_MAP0_S00_BASE)
TARGET_MAP0_S00_SRC		:= $(TARGET_MAP0_S00_NAME)
TARGET_MAP0_S00			:= $(BUILD_DIR)/VIN/MAP0_S00.BIN

TARGET_MAPS				:= $(TARGET_MAP0_S00)
TARGET_MAPS_NAMES		:= $(TARGET_MAP0_S00_NAME)

endif

TARGET_VIN				:= $(TARGET_STREAM) $(TARGET_CREDITS) \
							$(TARGET_OPTIONS) $(TARGET_SAVELOAD) \
							$(TARGET_MAPS)

TARGET_VIN_NAMES		:= $(TARGET_STREAM_SRC) $(TARGET_CREDITS_SRC) \
							$(TARGET_OPTIONS_SRC) $(TARGET_SAVELOAD_SRC) \
							$(TARGET_MAPS_NAMES)

endif

TARGET_NAMES			:= $(TARGET_MAIN_NAME) $(TARGET_1ST_NAMES) $(TARGET_VIN_NAMES)
TARGET_ALL				:= $(TARGET_MAIN) $(TARGET_1ST) $(TARGET_VIN)

# Source Definitions

CONFIG_FILES 			:= $(addsuffix .yaml,$(addprefix $(CONFIGS_DIR)/,$(TARGET_NAMES)))
LD_FILES	    		:= $(addsuffix .ld,$(addprefix $(LINKER_DIR)/,$(TARGET_NAMES)))

# Utils

# Function to find matching .s files for a target name
find_s_files 			= $(shell find $(ASM_DIR)/$(strip $1) -type f -path "*.s" -not -path "asm/*matchings*" 2> /dev/null)

# Function to find matching .c files for a target name
find_c_files 			= $(shell find $(C_DIR)/$(strip $1) -type f -path "*.c" 2> /dev/null)

# Function to generate matching .o files for a target name in the build directory
gen_o_files			 	= $(addprefix $(BUILD_DIR)/, \
							$(patsubst %.s, %.s.o, $(call find_s_files, $1)) \
							$(patsubst %.c, %.c.o, $(call find_c_files, $1)))

# Tools

CROSS					:= mips-linux-gnu
AS              		:= $(CROSS)-as
LD              		:= $(CROSS)-ld
OBJCOPY         		:= $(CROSS)-objcopy
OBJDUMP         		:= $(CROSS)-objdump
CPP             		:= $(CROSS)-cpp
CC              		:= $(TOOLS_DIR)/gcc-2.8.1-psx/cc1

PYTHON          		:= python3
SPLAT           		:= $(PYTHON) -m splat split
MASPSX					:= $(PYTHON) $(TOOLS_DIR)/maspsx/maspsx.py
DUMPSXISO				:= $(TOOLS_DIR)/psxiso/dumpsxiso
SILENT_ASSETS			:= $(PYTHON) $(TOOLS_DIR)/silentassets/extract.py

# Flags

OPT_FLAGS       		:= -O2
DL_FLAGS				:= -G4
ENDIAN          		:= -EL
INCLUDE_FLAGS			:= -Iinclude -I $(BUILD_DIR)
DEFINE_FLAGS   			:= -D_LANGUAGE_C -DUSE_INCLUDE_ASM
AS_FLAGS         		:= $(ENDIAN) $(INCLUDE_FLAGS) $(OPT_FLAGS) $(DL_FLAGS) -march=r3000 -mtune=r3000 -no-pad-sections
CC_FLAGS        		:= $(OPT_FLAGS) $(DL_FLAGS) -mips1 -mcpu=3000 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet
CPP_FLAGS				:= $(INCLUDE_FLAGS) $(DEFINE_FLAGS) -P -MMD -MP -undef -Wall -lang-c -nostdinc
LD_FLAGS				:= $(ENDIAN) $(OPT_FLAGS) -nostdlib --no-check-sections
OBJCOPY_FLAGS   		:= -O binary
OBJDUMP_FLAGS 			:= --disassemble-all --reloc --disassemble-zeroes -Mreg-names=32
SPLAT_FLAGS				:= --disassemble-all
MASPSX_FLAGS			:= --aspsx-version=2.77 --run-assembler $(AS_FLAGS)
DUMPSXISO_FLAGS			:= -x $(ROM_DIR) -s $(ROM_DIR)/layout.xml $(IMAGE_DIR)/$(GAME_NAME).bin
SILENT_ASSETS_FLAGS 	:= -exe $(ROM_DIR)/SLUS_007.07 -fs $(ROM_DIR)/SILENT. -fh $(ROM_DIR)/HILL. $(ASSETS_DIR)

# Rules

default: all

all: check

build: $(TARGET_ALL)

check: build
	@sha256sum --ignore-missing --check checksum.sha

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

# Recursive call to force order of operations
setup: clean-rom
	$(MAKE) extract
	$(MAKE) regenerate

# executable
$(TARGET_MAIN): $(TARGET_MAIN).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET_MAIN).elf: $(call gen_o_files, $(TARGET_MAIN_SRC))
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) 														\
		-Map $(TARGET_MAIN).map 						 					\
		-T $(LINKER_DIR)/$(TARGET_MAIN_NAME).ld 							\
		-T $(LINKER_DIR)/undefined_syms_auto.$(TARGET_MAIN_NAME).txt 		\
		-T $(LINKER_DIR)/undefined_funcs_auto.$(TARGET_MAIN_NAME).txt 		\
		-o $@

$(TARGET_BODYPROG): $(TARGET_BODYPROG).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET_BODYPROG).elf: $(call gen_o_files, $(TARGET_BODYPROG_SRC))
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) 															\
		-Map $(TARGET_BODYPROG).map 						 					\
		-T $(LINKER_DIR)/$(TARGET_BODYPROG_NAME).ld 							\
		-T $(LINKER_DIR)/undefined_syms_auto.$(TARGET_BODYPROG_NAME).txt 		\
		-T $(LINKER_DIR)/undefined_funcs_auto.$(TARGET_BODYPROG_NAME).txt 		\
		-o $@

$(TARGET_B_KONAMI): $(TARGET_B_KONAMI).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET_B_KONAMI).elf: $(call gen_o_files, $(TARGET_B_KONAMI_SRC))
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) 															\
		-Map $(TARGET_B_KONAMI).map 						 					\
		-T $(LINKER_DIR)/$(TARGET_B_KONAMI_NAME).ld 							\
		-T $(LINKER_DIR)/undefined_syms_auto.$(TARGET_B_KONAMI_NAME).txt 		\
		-T $(LINKER_DIR)/undefined_funcs_auto.$(TARGET_B_KONAMI_NAME).txt 		\
		-o $@

$(TARGET_STREAM): $(TARGET_STREAM).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET_STREAM).elf: $(call gen_o_files, $(TARGET_STREAM_SRC))
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) 															\
		-Map $(TARGET_STREAM).map 						 					\
		-T $(LINKER_DIR)/$(TARGET_STREAM_NAME).ld 							\
		-T $(LINKER_DIR)/undefined_syms_auto.$(TARGET_STREAM_NAME).txt 		\
		-T $(LINKER_DIR)/undefined_funcs_auto.$(TARGET_STREAM_NAME).txt 		\
		-o $@

$(TARGET_CREDITS): $(TARGET_CREDITS).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET_CREDITS).elf: $(call gen_o_files, $(TARGET_CREDITS_SRC))
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) 															\
		-Map $(TARGET_CREDITS).map 						 					\
		-T $(LINKER_DIR)/$(TARGET_CREDITS_DIR)/$(TARGET_CREDITS_NAME).ld 							\
		-T $(LINKER_DIR)/$(TARGET_CREDITS_DIR)/undefined_syms_auto.$(TARGET_CREDITS_NAME).txt 		\
		-T $(LINKER_DIR)/$(TARGET_CREDITS_DIR)/undefined_funcs_auto.$(TARGET_CREDITS_NAME).txt 		\
		-o $@

$(TARGET_OPTIONS): $(TARGET_OPTIONS).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET_OPTIONS).elf: $(call gen_o_files, $(TARGET_OPTIONS_SRC))
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) 															\
		-Map $(TARGET_OPTIONS).map 						 					\
		-T $(LINKER_DIR)/$(TARGET_OPTIONS_DIR)/$(TARGET_OPTIONS_NAME).ld 							\
		-T $(LINKER_DIR)/$(TARGET_OPTIONS_DIR)/undefined_syms_auto.$(TARGET_OPTIONS_NAME).txt 		\
		-T $(LINKER_DIR)/$(TARGET_OPTIONS_DIR)/undefined_funcs_auto.$(TARGET_OPTIONS_NAME).txt 		\
		-o $@

$(TARGET_SAVELOAD): $(TARGET_SAVELOAD).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET_SAVELOAD).elf: $(call gen_o_files, $(TARGET_SAVELOAD_SRC))
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) 															\
		-Map $(TARGET_SAVELOAD).map 						 					\
		-T $(LINKER_DIR)/$(TARGET_SAVELOAD_SRC).ld 							\
		-T $(LINKER_DIR)/$(TARGET_SAVELOAD_DIR)/undefined_syms_auto.$(TARGET_SAVELOAD_NAME).txt 		\
		-T $(LINKER_DIR)/$(TARGET_SAVELOAD_DIR)/undefined_funcs_auto.$(TARGET_SAVELOAD_NAME).txt 		\
		-o $@

$(TARGET_MAP0_S00): $(TARGET_MAP0_S00).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET_MAP0_S00).elf: $(call gen_o_files, $(TARGET_MAP0_S00_SRC))
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) 															\
		-Map $(TARGET_MAP0_S00).map 						 					\
		-T $(LINKER_DIR)/$(TARGET_MAP0_S00_NAME).ld 							\
		-T $(LINKER_DIR)/maps/undefined_syms_auto.$(TARGET_MAP0_S00_BASE).txt 		\
		-T $(LINKER_DIR)/maps/undefined_funcs_auto.$(TARGET_MAP0_S00_BASE).txt 		\
		-o $@

# generate objects
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

# split yaml
$(LINKER_DIR)/%.ld: $(CONFIG_DIR)/%.yaml
	@mkdir -p $(dir $@)
	$(SPLAT) $(SPLAT_FLAGS) $<

### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
