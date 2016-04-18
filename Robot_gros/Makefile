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

include $(PARENT_DIR)/hardware/common.rules
################################################################################
# Fichiers du projet

FICHIERS_C = \
	actions.c \
	actionneurs.c \
	communication.c \
	hardware/$(ARCH)/common.c \
	hardware/$(ARCH)/capteurIR.c \
	hardware/$(ARCH)/capteurUS.c \
	hardware/$(ARCH)/empileur.c \
	hardware/$(ARCH)/servos.c \

CFLAGS +=	-Ihardware/$(ARCH)/ \
			-Ihardware/

FICHIERS_O  += $(addprefix $(BUILD_DIR)/, $(FICHIERS_C:.c=.o) )

################################################################################
.PHONY: all view

# Règles de compilation de la "librairie stratégie"
_libStrat: $(BUILD_DIR)/libStrat.a

$(BUILD_DIR)/libStrat.a: $(FICHIERS_O)

# Règles de compilation de l'exécutable stratégie
all: $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(BUILD_DIR)/main.o libStrat libHardware libComm libCarto
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) -o $@ $(BUILD_DIR)/main.o $(BUILD_DIR)/libStrat.a $(CFLAGS) -lComm -lCarto -lHardware $(LDFLAGS)


$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/LowLevel
	@mkdir -p $(BUILD_DIR)/hardware/$(ARCH)

