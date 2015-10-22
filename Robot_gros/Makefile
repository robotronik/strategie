PROJECT=strategie2A
default: all
# Default Options
export ARCH  ?= stm32f407
export ROBOT ?= gros
export SDL   ?= no
export DEBUG ?= 0

PARENT_DIR = ../../

# Constantes de compilation
EXEC    = strategie_robot

include $(PARENT_DIR)/hardware/common.mk
################################################################################
# Fichiers du projet

FICHIERS_C = \
	main.c \
	actions.c \
	actionneurs.c \
	communication.c \
	LowLevel/capteurIR.c \
	LowLevel/capteurUS.c \
	LowLevel/empileur.c \
	LowLevel/servos.c \

FICHIERS_O  += $(addprefix $(BUILD_DIR)/, $(FICHIERS_C:.c=.o) )

################################################################################
.PHONY: all view

all: $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(FICHIERS_O) libHardware libCommStrat libCarto
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) -o $@ $(FICHIERS_O) $(CFLAGS) -lHardware -lCommStrat -lCarto $(LDFLAGS)


$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/LowLevel

