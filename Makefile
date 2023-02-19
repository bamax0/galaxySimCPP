CC=g++
LDFLAGS=
CCFLAGS=-Wall -Wextra -ansi -pedantic -std=c++17 -I./include -g -O3 -fopenmp -lm
PNGWRITTERFLAGS = -I/usr/local/include  -L/usr/local/lib -lPNGwriter -lpng -lz -lfreetype -I/usr/include/freetype2

BIN=./bin
OBJ=./obj
SRC=./src

SRC_FILE = $(wildcard $(SRC)/*.cpp)
OBJ_FILE = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILE))

DIRECTORY=bin obj include src data img
EXEC=main

all: prepare $(EXEC)

prepare: | $(DIRECTORY)

$(DIRECTORY): 
	mkdir -p $@

$(EXEC): $(OBJ_FILE)
	$(CC) -o $(BIN)/$@ $^ $(CCFLAGS) $(PNGWRITTERFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -o $@ -c $< $(CCFLAGS) $(PNGWRITTERFLAGS)


clean:
	rm -rf $(OBJ) $(LIB)
	rm -rf ./data
	rm -rf ./img

properclean: clean
	rm -rf $(BIN)
	rm -rf ./data
	rm -rf ./img


.PHONY: all prepare directory file clean properclean