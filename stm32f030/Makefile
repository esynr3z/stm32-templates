#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------
AS = arm-none-eabi-gcc
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OC = arm-none-eabi-objcopy
SZ = arm-none-eabi-size
OD = arm-none-eabi-objdump
RM = rm
MD = mkdir
#Detect Windows os to replace '/' to '\' for mkdir
ifeq ($(OS),Windows_NT)
	OSFIXPATH = $(subst /,\,$1)
else
	OSFIXPATH = $1
endif

################################################################################
#        ____             __ _                       _   _                     #
#       / ___|___  _ __  / _(_) __ _ _   _ _ __ __ _| |_(_) ___  _ __          #
#      | |   / _ \| '_ \| |_| |/ _` | | | | '__/ _` | __| |/ _ \| '_ \         #
#      | |__| (_) | | | |  _| | (_| | |_| | | | (_| | |_| | (_) | | | |        #
#       \____\___/|_| |_|_| |_|\__, |\__,_|_|  \__,_|\__|_|\___/|_| |_|        #
#                              |___/                                           #
#                                                                              #
################################################################################
#-------------------------------------------------------------------------------
# Project properties
#-------------------------------------------------------------------------------
PROJNAME = template
BUILDDIR = build
OBJDIR   = $(BUILDDIR)/obj
EXEDIR   = $(BUILDDIR)/exe
TARGET   = $(EXEDIR)/$(PROJNAME)
MISCINFO = $(BUILDDIR)/$(PROJNAME)

#-------------------------------------------------------------------------------
# Defines
#-------------------------------------------------------------------------------
DEFINES += USE_FULL_ASSERT=1
DEFINES += USE_STDPERIPH_DRIVER
DEFINES += STM32F030

#-------------------------------------------------------------------------------
# Paths
#-------------------------------------------------------------------------------
APP_PATH            = app
LIBS_PATH           = lib
DEVICE_SRC_PATH     = $(LIBS_PATH)/CMSIS_5/Device/ST/STM32F0xx/Source/GCC
DEVICE_INC_PATH     = $(LIBS_PATH)/CMSIS_5/Device/ST/STM32F0xx/Include
CMSIS_CORE_INC_PATH = $(LIBS_PATH)/CMSIS_5/CMSIS/Core/Include
SPL_SRC_PATH        = $(LIBS_PATH)/STM32F0xx_SPL_V1.5.0/src
SPL_INC_PATH        = $(LIBS_PATH)/STM32F0xx_SPL_V1.5.0/inc

#-------------------------------------------------------------------------------
# Startup
#-------------------------------------------------------------------------------
STARTUP = $(DEVICE_SRC_PATH)/startup_stm32f030.S

#-------------------------------------------------------------------------------
# Sources
#-------------------------------------------------------------------------------
SOURCEDIRS += $(APP_PATH)
SOURCEDIRS += $(DEVICE_SRC_PATH)
SOURCEDIRS += $(SPL_SRC_PATH)

#-------------------------------------------------------------------------------
# Includes
#-------------------------------------------------------------------------------
INCLUDEDIRS += $(APP_PATH)
INCLUDEDIRS += $(DEVICE_INC_PATH)
INCLUDEDIRS += $(CMSIS_CORE_INC_PATH)
INCLUDEDIRS += $(SPL_INC_PATH)

#-------------------------------------------------------------------------------
# Libs
#-------------------------------------------------------------------------------
LIBDIRS +=
LIBS    +=

#-------------------------------------------------------------------------------
# C compiler options
#-------------------------------------------------------------------------------
CFLAGS += -mthumb -mcpu=cortex-m0
CFLAGS += -mfloat-abi=soft
CFLAGS += -std=gnu99
CFLAGS += -Wall
CFLAGS += -Os
CFLAGS += -g
CFLAGS += -fvisibility=default
CFLAGS += -fno-builtin
CFLAGS += -fdata-sections
CFLAGS += -ffunction-sections
#CFLAGS += -flto
CFLAGS += $(addprefix -I, $(INCLUDEDIRS))
CFLAGS += $(addprefix -D, $(DEFINES))

#-------------------------------------------------------------------------------
# Asm compiler options
#-------------------------------------------------------------------------------
ASFLAGS += $(addprefix -D, $(DEFINES))

#-------------------------------------------------------------------------------
# Linker script
#-------------------------------------------------------------------------------
LDSCRIPT = $(DEVICE_SRC_PATH)/STM32F030F4P6.ld

#-------------------------------------------------------------------------------
# Linker options
#-------------------------------------------------------------------------------
LDFLAGS += -mthumb -mcpu=cortex-m0
LDFLAGS += -mfloat-abi=soft
LDFLAGS += -T$(LDSCRIPT)
LDFLAGS += --specs=nano.specs --specs=nosys.specs
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,-Map=$(TARGET).map
LDFLAGS += -lgcc -lc
LDFLAGS += $(addprefix -L, $(LIBDIRS))
LDFLAGS += $(LIBS)

#-------------------------------------------------------------------------------
# Object files
#-------------------------------------------------------------------------------
OBJS += $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(wildcard  $(addsuffix /*.c, $(SOURCEDIRS)))))
OBJS += $(addprefix $(OBJDIR)/, $(patsubst %.S, %.o, $(wildcard  $(addsuffix /*.S, $(SOURCEDIRS)))))
OBJS += $(addprefix $(OBJDIR)/, $(patsubst %.S, %.o, $(STARTUP)))

#-------------------------------------------------------------------------------
# Files to remove with "make clean" 
#-------------------------------------------------------------------------------
TOREMOVE += $(BUILDDIR)

################################################################################
#                      _____                    _                              #
#                     |_   _|_ _ _ __ __ _  ___| |_ ___                        #
#                       | |/ _` | '__/ _` |/ _ \ __/ __|                       #
#                       | | (_| | | | (_| |  __/ |_\__ \                       #
#                       |_|\__,_|_|  \__, |\___|\__|___/                       #
#                                    |___/                                     #
#                                                                              #
################################################################################
#===============================================================================
# Make all targets
#===============================================================================
all: $(TARGET).hex $(TARGET).bin $(MISCINFO).dasm size

#===============================================================================
# HEX generation
#===============================================================================
$(TARGET).hex: $(TARGET).elf
	@echo "Create" $@ "from" $<
	@$(OC) -Oihex $< $@

#===============================================================================
# BIN generation
#===============================================================================
$(TARGET).bin: $(TARGET).elf
	@echo "Create" $@ "from" $<
	@$(OC) -Obinary $< $@

#===============================================================================
# Disasm generation
#===============================================================================
$(MISCINFO).dasm: $(TARGET).elf
	@echo "Create" $@ "from" $<
	@$(OD) -DS $< > $@

#===============================================================================
# Size
#===============================================================================
size: $(TARGET).elf
	@echo "-- Size ---------------------------------------------"
	@$(SZ) $^

#===============================================================================
# Linking
#===============================================================================
$(TARGET).elf: $(OBJS)
	@$(MD) -p $(call OSFIXPATH,$(dir $@))
	@echo "LD" $^
	@$(LD) $(LDFLAGS) $^ -o $@

#===============================================================================
# Compiling
#===============================================================================
$(OBJDIR)/%.o: %.c
	@echo "CC" $<
	@$(MD) -p $(call OSFIXPATH,$(dir $@))
	@$(CC) $(CFLAGS) -MD -c $< -o $@

$(OBJDIR)/%.o: %.S
	@echo "AS" $<
	@$(MD) -p $(call OSFIXPATH,$(dir $@))
	@$(AS) $(ASFLAGS) -c $< -o $@

#===============================================================================
# Clean
#===============================================================================
clean:
	@$(RM) -rf $(TOREMOVE)

################################################################################
#                             __  __ _                                         #
#                            |  \/  (_)                                        #
#                            | \  / |_ ___  ___                                #
#                            | |\/| | / __|/ __|                               #
#                            | |  | | \__ \ (__                                #
#                            |_|  |_|_|___/\___|                               #
#                                                                              #
################################################################################
#===============================================================================
# Generate Qt basic project
#===============================================================================
#In Windows this work in semiauto mode - you need to replace all "\n" to actual newline chars manualy
#¯\_(ツ)_/¯
QTPROJ_CONFIG = $(subst =, " ", $(addprefix "\#define ", $(addsuffix "\n", $(DEFINES))))
QTPROJ_FILES += $(addsuffix "\n", $(wildcard  $(addsuffix /*.c, $(SOURCEDIRS))))
QTPROJ_FILES += $(addsuffix "\n", $(wildcard  $(addsuffix /*.h, $(SOURCEDIRS))))
QTPROJ_FILES += $(addsuffix "\n", $(wildcard  $(addsuffix /*.S, $(SOURCEDIRS))))
QTPROJ_FILES += $(addsuffix "\n", $(wildcard  $(addsuffix /*.h, $(INCLUDEDIRS))))
QTPROJ_CREATOR = "[General]"
QTPROJ_INCLUDES = $(addsuffix "\n", $(INCLUDEDIRS))
qtproj:
	@echo "Generate Qt basic project:"
	@echo "	clear previous project files"
	@$(RM) -f *.config *.creator *.files *.includes
	@echo "	create" $(PROJNAME).config
	@echo "// Predefined macros in your project" > $(PROJNAME).config
	@echo $(QTPROJ_CONFIG) >> $(PROJNAME).config
	@echo "	create" $(PROJNAME).creator
	@echo $(QTPROJ_CREATOR) > $(PROJNAME).creator
	@echo "	create" $(PROJNAME).files
	@echo "// Files in your project" > $(PROJNAME).files
	@echo $(QTPROJ_FILES) >> $(PROJNAME).files
	@echo "	create" $(PROJNAME).includes
	@echo "// Include dirs in your project" > $(PROJNAME).includes
	@echo $(QTPROJ_INCLUDES) >> $(PROJNAME).includes