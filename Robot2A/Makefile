
# Options prises en compte :
#    SDL=yes       pour utiliser le simulateur
#    DEBUG=yes     pour activer le debug

# Cibles :
#    run: lance l'executable
#    all: créer l'executable
#    demo: lance un ensemble de commande au robot

################################################################################
# Variables de compilation

include ../../stm32f407/stm32f407.mk

# Variables d'environnement
EXEC = strategie_robot
CARTO_HEADER = ../../cartographie/pathfinding.h
STM32_Dir = ../../stm32f407/


# Chemin du dépôt stm32f407
# /!\ Doit être le chemin absolu. Pas relatif.
PathSTM32 = ../../stm32f407/

# options
DEBUG = yes

################################################################################

SOURCES=main.c \
		actionneurs.c \
		communication.c \
		LowLevel/capteurIR.c \
		LowLevel/capteurUS.c \
		LowLevel/empileur.c \
		LowLevel/servos.c \

HEADERS=$(SOURCES:.c=.h)
OBJECTS=$(SOURCES:.c=.o)

SOURCEFILES=main.c $(SOURCES) $(HEADERS)


ifeq ($(DEBUG),yes)
	DEBUGFLAGS = -DDEBUG=1 -g
else
	DEBUGFLAGS = -DDEBUG=0
endif

################################################################################

all:
	@make -s -C $(STM32_Dir) $@

##### Envoi du binaire sur le STM32
flash: 
	make -C $(STM32_Dir) $@

##### Débug
debug:
	make -C $(STM32_Dir) $@

debug1:
	make -C $(STM32_Dir) $@

debug2:
	make -C $(STM32_Dir) $@



##### Création du .a nécessaire au stm32
libStrategie.a: $(OBJECTS)
	@echo "	AR	$@"
	@$(AR) -r $@ $(OBJECTS)
	@echo "	RANLIB	$@"
	@ranlib $@

%.o: %.c
	@echo "	CC	$@"
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ -c $<

##### Nettoyage
.PHONY: clean cleanDist cleanLib bclean mrproper

clean:
	rm -f $(OBJECTS)
	rm -f libStrategie.a

cleanDist: clean
	$(MAKE) -C $(STM32_Dir) clean

bclean:
	$(MAKE) -C $(STM32_Dir) $@
