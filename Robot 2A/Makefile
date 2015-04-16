
# Variables de compilation

CC = gcc
AR = ar
CFLAGS  = -W -Wall -fdiagnostics-color=auto -std=c99
LDFLAGS = -lm

# Variables d'environnement
EXEC = strategie_robot
CARTO_DIR = ../../cartographie/
CARTO_LIB = libCARTOGRAPHIE.a
CARTO_LIB_FULL_PATH = $(CARTO_DIR)$(CARTO_LIB)
CARTO_HEADER = pathfinding.h

# options
DEBUG = yes

################################################################################

SOURCES=main.c \
		actionneurs.c \

HEADERS=$(SOURCES:.c=.h)
OBJECTS=$(SOURCES:.c=.o)

SOURCEFILES=main.c $(SOURCES) $(HEADERS)


ifeq ($(DEBUG),yes)
	CFLAGS += -DDEBUG=1 -g
endif

################################################################################

.PHONY:view

view: all
	./$(EXEC)

all: $(EXEC)

$(EXEC): $(OBJECTS) $(CARTO_LIB_FULL_PATH)
	$(CC) $(CFLAGS) -o $@ $^ $(CARTO_LIB_FULL_PATH) $(LDFLAGS)

$(CARTO_LIB_FULL_PATH):
	cd $(CARTO_DIR) && make $(CARTO_LIB) SDL=no DEBUG=$(DEBUG)

%.o: %.cd
	$(CC) $(CFLAGS) -o $@ -c $<

tarall: $(SOURCEFILES)
	tar -jcvf $(EXEC).tar.bz2 $^

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -rf $(EXEC) $(EXEC).tar.bz2
	cd $(CARTO_DIR) && make clean
	
