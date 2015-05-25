PROJECT=strategie2A
default: all
# Default Options
export ARCH  = STM32F407
export ROBOT = gros
export SDL   = no
export DEBUG = _WARNING_

export PARENT_DIR = ../../
include $(PARENT_DIR)/common_code/common.mk

# Constantes de compilation
EXEC    = strategie_robot
LIBSTRAT= libStrategie

################################################################################
# Fichiers du projet

FICHIERS_C = \
	main.c \
	actionneurs.c \
	communication.c \
	LowLevel/capteurIR.c \
	LowLevel/capteurUS.c \
	LowLevel/empileur.c \
	LowLevel/servos.c \
	actions.c \

FICHIERS_H = $(SOURCES:.c=.h)
FICHIERS_O  += $(addprefix $(BUILD_DIR)/, $(FICHIERS_C:.c=.o) )

################################################################################

all: $(EXEC)

##### Envoi du binaire sur le STM32
flash:
	make -C $(STM32_Dir) $@

##### Création du .a nécessaire au stm32
.PHONY:view

libStrategie: $(BUILD_DIR)/libStrategie.a

view: $(EXEC)
	./$^

$(EXEC): $(FICHIERS_O)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(BUILD_DIR)/libStrategie.a: $(FICHIERS_O)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/Calibration
	@mkdir -p $(BUILD_DIR)/LowLevel

################################################################################
# Cibles génériques

mrproper: clean
	@echo "Hard-cleaning  $(PROJECT) directory…"
	@rm -rf $(EXEC) $(PIC_ELF) $(PIC_HEX)
