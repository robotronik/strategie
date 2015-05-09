
# Options prises en compte :
#    SDL=yes       pour utiliser le simulateur
#    DEBUG=yes     pour activer le debug

# Cibles :
#    run: lance l'executable
#    all: créer l'executable
#    demo: lance un ensemble de commande au robot

################################################################################
# Variables de compilation

CC = gcc
AR = ar
CFLAGS  = -W -Wall -fdiagnostics-color=auto -std=c99
LDFLAGS = -lm

# Variables d'environnement
EXEC = strategie_robot
CARTO_HEADER = ../../cartographie/pathfinding.h
STM32_Dir = ../../stm32f407/


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
	make -C $(STM32_Dir) $@

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
	$(AR) -r $@ $(OBJECTS)
	ranlib $@

%.o: %.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ -c $<

tarall: $(SOURCEFILES)
	tar -jcvf $(EXEC).tar.bz2 $^

.PHONY: clean
clean:
	rm -f $(OBJECTS)

cleanAll:
	make -C $(STM32_Dir) clean


mrproper: clean
	rm -rf $(EXEC) $(EXEC).tar.bz2
