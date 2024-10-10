# Names and Paths

GAME_NAME			:= SLUS-00707
MAIN_NAME   		:= SLUS_007.07
SEG_1_NAME			:= SILENT
SEG_2_NAME			:= HILL

ROM_DIR				:= rom
CONFIG_DIR			:= configs
LINKER_DIR	       	:= linkers
IMAGE_DIR			:= $(ROM_DIR)/image
BUILD_DIR       	:= build
TOOLS_DIR       	:= tools
ASSETS_DIR			:= assets
ASM_DIR				:= asm
C_DIR_MAIN			:= src

CONFIG_FILES 		:= $(foreach dir,$(CONFIG_DIR),$(wildcard $(dir)/*.yaml))
LD_FILES	    	:= $(foreach f,$(CONFIG_FILES),$(patsubst %.yaml,%.ld,$(LINKER_DIR)/$(notdir $f)))

# Targets

TARGET_MAIN 		:= executable
TARGET_1ST 			:= bodyprog
TARGET_BIN 			:=

# Source Definitions
ASM_DIRS_BOOT      	:= $(shell find asm/main -type d -not -path "asm/*matchings*" -not -path "asm/lib/*")
C_DIR_BOOT			:= src
S_FILES_BOOT		:= $(foreach dir,$(ASM_DIRS_BOOT),$(wildcard $(dir)/*.s))
C_FILES_BOOT		:= $(foreach dir,$(C_DIR_BOOT),$(wildcard $(dir)/*.c))

O_FILES_BOOT		:= $(foreach file,$(S_FILES_BOOT),$(BUILD_DIR)/$(file).o) \
						$(foreach file,$(C_FILES_BOOT),$(BUILD_DIR)/$(file).o) \
						$(foreach file,$(BIN_FILES_BOOT),$(BUILD_DIR)/$(file).o)

ASM_DIRS_ALL		:= $(ASM_DIRS_BOOT)
C_DIRS_ALL			:= $(C_DIR_BOOT)
BIN_DIRS_ALL		:= $(BIN_DIR_BOOT)

# Tools
CROSS				:= mips-linux-gnu
AS              	:= $(CROSS)-as
LD              	:= $(CROSS)-ld
OBJCOPY         	:= $(CROSS)-objcopy
OBJDUMP         	:= $(CROSS)-objdump
CPP             	:= $(CROSS)-cpp
CC              	:= $(TOOLS_DIR)/gcc-2.8.1-psx/cc1

PYTHON          	:= python3
SPLAT           	:= $(PYTHON) -m splat split
MASPSX				:= $(PYTHON) $(TOOLS_DIR)/maspsx/maspsx.py
DUMPSXISO			:= $(TOOLS_DIR)/psxiso/dumpsxiso
SILENT_ASSETS		:= $(PYTHON) $(TOOLS_DIR)/silentassets/extract.py

# Flags
OPT_FLAGS       	:= -O2
DL_FLAGS			:= -G4
ENDIAN          	:= -EL
INCLUDE_FLAGS		:= -Iinclude -I $(BUILD_DIR)
DEFINE_FLAGS   		:= -D_LANGUAGE_C -DUSE_INCLUDE_ASM
AS_FLAGS         	:= $(ENDIAN) $(INCLUDE_FLAGS) $(OPT_FLAGS) $(DL_FLAGS) -march=r3000 -mtune=r3000 -no-pad-sections
CC_FLAGS        	:= $(OPT_FLAGS) $(DL_FLAGS) -mips1 -mcpu=3000 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -quiet
CPP_FLAGS			:= $(INCLUDE_FLAGS) $(DEFINE_FLAGS) -P -MMD -MP -undef -Wall -lang-c -nostdinc
LD_FLAGS			:= $(ENDIAN) $(OPT_FLAGS) -nostdlib --no-check-sections
OBJCOPY_FLAGS   	:= -O binary
OBJDUMP_FLAGS 		:= --disassemble-all --reloc --disassemble-zeroes -Mreg-names=32
SPLAT_FLAGS			:= --disassemble-all
MASPSX_FLAGS		:= --aspsx-version=2.77 --run-assembler $(AS_FLAGS)
DUMPSXISO_FLAGS		:= -x $(ROM_DIR) -s $(ROM_DIR)/layout.xml $(IMAGE_DIR)/$(GAME_NAME).bin
SILENT_ASSETS_FLAGS := -exe $(ROM_DIR)/SLUS_007.07 -fs $(ROM_DIR)/SILENT. -fh $(ROM_DIR)/HILL. $(ASSETS_DIR)

# Rules
default: all

all: dirs check

check: $(BUILD_DIR)/$(TARGET_MAIN)
	@sha256sum --ignore-missing --check checksum.sha

extract:
	$(DUMPSXISO) $(DUMPSXISO_FLAGS)
	$(SILENT_ASSETS) $(SILENT_ASSETS_FLAGS)

generate: $(LD_FILES)

dirs:
	$(foreach dir,$(ASM_DIRS_ALL) $(C_DIRS_ALL) $(BIN_DIRS_ALL),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

clean:
	rm -rf $(BUILD_DIR)

clean-rom:
	find rom -maxdepth 1 -type f -delete

reset: clean
	rm -rf $(ASM_DIR)
	rm -rf $(LINKER_DIR)
	rm -rf meta/*auto*.txt 

setup: | clean reset clean-rom extract generate

regenerate: | clean reset generate

# executable
$(BUILD_DIR)/$(TARGET_MAIN): $(BUILD_DIR)/$(TARGET_MAIN).elf
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(BUILD_DIR)/$(TARGET_MAIN).elf: $(O_FILES_BOOT)
	$(LD) $(LD_FLAGS) 												 \
		-Map $(BUILD_DIR)/$(TARGET_MAIN).map 						 \
		-T $(LINKER_DIR)/$(MAIN_NAME).ld 							 \
		-T meta/$(MAIN_NAME).undefined_syms_auto.txt 				 \
		-T meta/$(MAIN_NAME).undefined_funcs_auto.txt 				 \
		-o $@

# split yaml
$(LINKER_DIR)/%.ld: $(CONFIG_DIR)/%.yaml
	@mkdir -p $(dir $@)
	$(SPLAT) $(SPLAT_FLAGS) $<

# generate objects
$(BUILD_DIR)/%.i: %.c
	$(CPP) -P -MMD -MP -MT $@ -MF $@.d $(CPP_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.s: $(BUILD_DIR)/%.i
	$(CC) $(CC_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.o: $(BUILD_DIR)/%.c.s
	$(MASPSX) $(MASPSX_FLAGS) -o $@ $<
	$(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<

### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
