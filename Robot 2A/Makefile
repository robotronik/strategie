
# Variables de compilation

CC = gcc
AR = ar
CFLAGS  = -W -Wall -fdiagnostics-color=auto -std=c99
LDFLAGS = -lm

# Variables d'environnement
EXEC = strategie_robot
CARTO_DIR = ../../cartographie/
CARTO_LIB = libCARTOGRAPHIE.a
CARTO_HEADER = pathfinding.h

################################################################################

SOURCES=main.c \
		actionneurs.c \

HEADERS=$(SOURCES:.c=.h)
OBJECTS=$(SOURCES:.c=.o)

SOURCEFILES=main.c $(SOURCES) $(HEADERS)

################################################################################

.PHONY:view

view: all
	./$(EXEC)

all: $(EXEC)

$(EXEC): $(OBJECTS) $(CARTO_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(CARTO_LIB) $(LDFLAGS)

$(CARTO_LIB): $(CARTO_DIR)$(CARTO_LIB)
	cp $(CARTO_DIR)$(CARTO_LIB) .

$(CARTO_DIR)$(CARTO_LIB):
	cd $(CARTO_DIR) && make $(CARTO_LIB) SDL=no

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

tarall: $(SOURCEFILES)
	tar -jcvf $(EXEC).tar.bz2 $^

clean:
	rm -f $(OBJECTS) $(CARTO_LIB)

mrproper: clean
	rm -rf $(EXEC) $(EXEC).tar.bz2
	cd $(CARTO_DIR) && make clean
	
