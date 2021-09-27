BOOT_BASENAME   := SCUS_941
COMMON_BASENAME	:= common

BUILD_DIR       := build
TOOLS_DIR       := tools

TARGET_BOOT		:= $(BUILD_DIR)/$(BOOT_BASENAME)
GAMEBIN_DIR		:= $(BOOT_BASENAME)

# boot loader (identical on all disks, SCUS_941.63, SCUS_941.64, SCUS_941.65)
ASM_BOOT_DIR	:= asm/boot
C_BOOT_DIR		:= src/boot
ASSETS_BOOT_DIR	:= assets/boot

ASM_BOOT_DIRS	:= $(ASM_BOOT_DIR) $(ASM_BOOT_DIR)/data
C_BOOT_DIRS		:= $(C_BOOT_DIR)
BIN_BOOT_DIRS	:= $(ASSETS_BOOT_DIR)

S_BOOT_FILES	:= $(foreach dir,$(ASM_BOOT_DIRS),$(wildcard $(dir)/*.s))
C_BOOT_FILES	:= $(foreach dir,$(C_BOOT_DIRS),$(wildcard $(dir)/*.c))
BIN_BOOT_FILES	:= $(foreach dir,$(BIN_BOOT_DIRS),$(wildcard $(dir)/*.bin))

O_BOOT_FILES	:= $(foreach file,$(S_BOOT_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(C_BOOT_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(BIN_BOOT_FILES),$(BUILD_DIR)/$(file).o)

# common (here for example)
ASM_$(COMMON_BASENAME)_DIR		:= asm/$(COMMON_BASENAME)
C_$(COMMON_BASENAME)_DIR		:= src/$(COMMON_BASENAME)
ASSETS_$(COMMON_BASENAME)_DIR	:= assets/$(COMMON_BASENAME)

ASM_$(COMMON_BASENAME)_DIRS		:= $(ASM_$(COMMON_BASENAME)_DIR) $(ASM_$(COMMON_BASENAME)_DIR)/data
C_$(COMMON_BASENAME)_DIRS		:= $(C_$(COMMON_BASENAME)_DIR)
BIN_$(COMMON_BASENAME)_DIRS		:= $(ASSETS_$(COMMON_BASENAME)_DIR)

S_$(COMMON_BASENAME)_FILES		:= $(foreach dir,$(ASM_$(COMMON_BASENAME)_DIRS),$(wildcard $(dir)/*.s))
C_$(COMMON_BASENAME)_FILES		:= $(foreach dir,$(C_$(COMMON_BASENAME)_DIRS),$(wildcard $(dir)/*.c))
BIN_$(COMMON_BASENAME)_FILES	:= $(foreach dir,$(BIN_$(COMMON_BASENAME)_DIRS),$(wildcard $(dir)/*.bin))

O_$(COMMON_BASENAME)_FILES		:= $(foreach file,$(S_$(COMMON_BASENAME)_FILES),$(BUILD_DIR)/$(file).o) \
									$(foreach file,$(C_$(COMMON_BASENAME)_FILES),$(BUILD_DIR)/$(file).o) \
									$(foreach file,$(BIN_$(COMMON_BASENAME)_FILES),$(BUILD_DIR)/$(file).o)

# batch
ALL_ASM_DIRS	:= $(ASM_BOOT_DIRS) $(ASM_$(COMMON_BASENAME)_DIRS)
ALL_C_DIRS		:= $(C_BOOT_DIRS) $(C_$(COMMON_BASENAME)_DIRS)
ALL_BIN_DIRS	:= $(BIN_BOOT_DIRS) $(BIN_$(COMMON_BASENAME)_DIRS)
ALL_ASSETS_DIRS	:= $(ASSETS_BOOT_DIR) $(ASSETS_$(COMMON_BASENAME)_DIR)

# TOOLS
MAKE            := make
PYTHON          := python3
WINE            := wine
SED             := sed
UNIX2DOS        := unix2dos
CPP             := cpp -P
CROSS			:= mips-elf-
AS              := $(CROSS)as -EL
LD              := $(CROSS)ld -EL
OBJCOPY         := $(CROSS)objcopy
CC_PSYQ_41      := $(WINE) $(TOOLS_DIR)/psyq/4.1/CC1PSX.EXE
CC_PSYQ_43      := $(WINE) $(TOOLS_DIR)/psyq/4.3/CC1PSX.EXE
CC_PSYQ_46      := $(WINE) $(TOOLS_DIR)/psyq/4.6/CC1PSX.EXE
CC              := $(CC_PSYQ_41)
SPLAT           := $(PYTHON) $(TOOLS_DIR)/splat/split.py

# FLAGS
AS_INCLUDES     := -Iinclude
AS_FLAGS        := -march=r3000 -mtune=r3000
AS_FLAGS        += $(AS_INCLUDES)
CPP_INCLUDES    := -Iinclude
CPP_FLAGS       := -undef -Wall -lang-c
CPP_FLAGS       += -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C
CPP_FLAGS       += $(CPP_INCLUDES)

ifdef PERMUTER
CPP_FLAGS       += -DPERMUTER
endif

CC_FLAGS        := -quiet -G0 -Wall
OPT_FLAGS       := -O2

OBJCOPY_FLAGS   := -O binary

# Rules

default: all

all: dirs $(TARGET_BOOT) check

check: $(TARGET_BOOT)
	@echo "$$(cat $(GAMEBIN_DIR)/$(BOOT_BASENAME).sha1) $<" | sha1sum --check
	@touch $@

dirs:
	$(foreach dir,$(ALL_ASM_DIRS) $(ALL_C_DIRS) $(ALL_BIN_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

setup: $(BOOT_BASENAME).yaml
	$(SPLAT) $(BOOT_BASENAME).yaml

clean:
	rm -rf $(BUILD_DIR)

nuke: clean
	rm -rf asm
	rm -rf assets
	rm -rf *auto*.txt
	rm -rf *.ld

# bootloader
$(TARGET_BOOT): $(TARGET_BOOT).elf
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

$(TARGET_BOOT).elf: $(O_BOOT_FILES)
	$(LD) -Map $(BUILD_DIR)/$(BOOT_BASENAME).map -T $(BOOT_BASENAME).ld -T undefined_syms_auto.$(BOOT_BASENAME).txt -T undefined_funcs_auto.$(BOOT_BASENAME).txt -T undefined_syms.$(BOOT_BASENAME).txt --no-check-sections -o $@

# generate objects
$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<

$(BUILD_DIR)/%.c.o: %.c
	$(CPP) $(CPP_FLAGS) $(CPP_TARGET) $< | $(UNIX2DOS) | $(CC) $(CC_FLAGS) $(OPT_FLAGS) | $(AS) $(AS_FLAGS) -o $@

# keep .obj files
.SECONDARY:

.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail