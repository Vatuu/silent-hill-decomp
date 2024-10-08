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
PYTHON          	:= python3
CROSS				:= mips-linux-gnu
AS              	:= $(CROSS)-as -EL
LD              	:= $(CROSS)-ld -EL
OBJCOPY         	:= $(CROSS)-objcopy
CPP              	:= cpp
CC              	:= $(TOOLS_DIR)/psyq/CC1PSX
SPLAT           	:= $(PYTHON) -m splat
DUMPSXISO			:= $(TOOLS_DIR)/psxiso/dumpsxiso
SILENT_ASSETS		:= $(PYTHON) $(TOOLS_DIR)/silentassets/extract.py

# Flags
OPT_FLAGS       	:= -O2
INCLUDE_CFLAGS		:= -Iinclude
AS_FLAGS        	:= -march=r3000 -mtune=r3000 -Iinclude
D_FLAGS       		:= -D_LANGUAGE_C
CC_FLAGS        	:= -G 0 -mips1 -mcpu=3000 -mgas -msoft-float $(OPT_FLAGS) -fgnu-linker  -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -mgas -fgnu-linker -mips1 -mcpu=3000
CPP_FLAGS       	:= -undef -Wall -lang-c $(DFLAGS) $(INCLUDE_CFLAGS) -nostdinc
OBJCOPY_FLAGS   	:= -O binary
DUMPSXISO_FLAGS		:= -x $(ROM_DIR) -s $(ROM_DIR)/layout.xml $(IMAGE_DIR)/$(GAME_NAME).bin
SILENT_ASSETS_FLAGS := -exe $(ROM_DIR)/SLUS_007.07 -fs $(ROM_DIR)/SILENT. -fh $(ROM_DIR)/HILL. $(ASSETS_DIR)

# Rules
default: all

all: dirs check

check: $(TARGET_MAIN)
	cat $(ROM_DIR)/sha1/$(MAIN_NAME).sha1
	sha1sum $<

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

reset:
	rm -rf $(ASM_DIR)
	rm -rf $(LINKER_DIR)
	rm -rf meta/*auto*.txt 

setup: | clean reset clean-rom extract generate

regenerate: | clean reset generate

# executable
$(TARGET_MAIN): $(TARGET_MAIN).elf
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET_MAIN).elf: $(O_FILES_BOOT)
	$(LD) -Map $(TARGET_MAIN).map -T $(LINKER_DIR)/$(MAIN_NAME).ld -T meta/$(MAIN_NAME).undefined_syms_auto.txt -T meta/$(MAIN_NAME).undefined_funcs_auto.txt --no-check-sections -o $@

# split yaml
$(LINKER_DIR)/%.ld: $(CONFIG_DIR)/%.yaml
	@mkdir -p $(dir $@)
	$(SPLAT) split $<

# generate objects
$(BUILD_DIR)/%.i: %.c
	$(CPP) -P -MMD -MP -MT $@ -MF $@.d $(CPP_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.s: $(BUILD_DIR)/%.i
	$(CC) $(CC_FLAGS) -o $@ $<

$(BUILD_DIR)/%.c.o: $(BUILD_DIR)/%.c.s
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<

### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
