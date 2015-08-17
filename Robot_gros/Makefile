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
HEX 	= strategie_robot.hex

include $(PARENT_DIR)/hardware/common.mk
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

.PHONY:view
view: $(EXEC)
	./$^

$(HEX): $(EXEC)

$(EXEC): $(FICHIERS_O) $(HARDW_LIB)
	@make -C $(COMMUNICATION_DIR) libCommStrat
	@make -C $(CARTO_DIR) libCartographie
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) -o $@ $^ $(CFLAGS) -lCommStrat -lCartographie $(LDFLAGS)

$(HARDW_LIB): hardware_lib

$(BUILD_DIR)/libStrategie.a: $(FICHIERS_O)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/Calibration
	@mkdir -p $(BUILD_DIR)/LowLevel

################################################################################
# Cibles génériques

mrproper: clean
	@echo "Hard-cleaning  $(PROJECT) directory…"
	@rm -rf $(EXEC) $(HEX)

