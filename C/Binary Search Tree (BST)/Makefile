# Ryan Lee
# Makefile
# A Makefile with macros

ADT_NAME = BST
SOURCES = $(ADT_NAME).c $(ADT_NAME)Client.c
OBJECTS = $(ADT_NAME)Client.o $(ADT_NAME).o
HEADERS = $(ADT_NAME).h
EXEBIN = $(ADT_NAME)Client
FLAGS = -std=c99 -Wall

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
        gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
        gcc -c $(FLAGS) $(SOURCES)

clean:
        rm -f $(EXEBIN) $(OBJECTS)

check:
        valgrind --leak-check=full $(EXEBIN)