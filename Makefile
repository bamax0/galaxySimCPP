CC=g++
LDFLAGS=
CCFLAGS=-Wall -Wextra -ansi -pedantic -std=c++11 -I./include -g -O3 -ffast-math -fopenmp -lm

BIN=./bin
OBJ=./obj
SRC=./src

SRC_FILE = $(wildcard $(SRC)/*.cpp)
OBJ_FILE = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILE))

DIRECTORY=bin obj include src
EXEC=main

all: prepare $(EXEC)

prepare: | $(DIRECTORY)

$(DIRECTORY): 
	mkdir -p $@
$(EXEC): $(OBJ_FILE)
	$(CC) -o $(BIN)/$@ $^ $(CCFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -o $@ -c $< $(CCFLAGS)

clean:
	rm -rf $(OBJ) $(LIB)

properclean: clean
	rm -rf $(BIN)


.PHONY: all prepare directory file clean properclean