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
TARGET_MAIN 			:= $(BUILD_DIR)/SLUS_007.07

TARGET_BODYPROG_NAME	:= bodyprog
TARGET_BODYPROG			:= $(BUILD_DIR)/1ST/BODYPROG.BIN

TARGET_STREAM_NAME		:= stream
TARGET_STREAM			:= $(BUILD_DIR)/VIN/STREAM.BIN

TARGET_ALL				:= $(TARGET_MAIN) $(TARGET_BODYPROG) $(TARGET_STREAM)

# Source Definitions

CONFIG_FILES 			:= $(foreach dir,$(CONFIG_DIR),$(wildcard $(dir)/*.yaml))
LD_FILES	    		:= $(foreach f,$(CONFIG_FILES),$(patsubst %.yaml,%.ld,$(LINKER_DIR)/$(notdir $f)))

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

$(TARGET_MAIN).elf: $(call gen_o_files, $(TARGET_MAIN_NAME))
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

$(TARGET_BODYPROG).elf: $(call gen_o_files, $(TARGET_BODYPROG_NAME))
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) 															\
		-Map $(TARGET_BODYPROG).map 						 					\
		-T $(LINKER_DIR)/$(TARGET_BODYPROG_NAME).ld 							\
		-T $(LINKER_DIR)/undefined_syms_auto.$(TARGET_BODYPROG_NAME).txt 		\
		-T $(LINKER_DIR)/undefined_funcs_auto.$(TARGET_BODYPROG_NAME).txt 		\
		-o $@

$(TARGET_STREAM): $(TARGET_STREAM).elf
	@mkdir -p $(dir $@)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET_STREAM).elf: $(call gen_o_files, $(TARGET_STREAM_NAME))
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) 															\
		-Map $(TARGET_STREAM).map 						 					\
		-T $(LINKER_DIR)/$(TARGET_STREAM_NAME).ld 							\
		-T $(LINKER_DIR)/undefined_syms_auto.$(TARGET_STREAM_NAME).txt 		\
		-T $(LINKER_DIR)/undefined_funcs_auto.$(TARGET_STREAM_NAME).txt 		\
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
