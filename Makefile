CC=g++
LDFLAGS=
CCFLAGS=-Wall -Wextra -ansi -pedantic -std=c++11 -I./include -g -O3 -fopenmp -lm 

BIN=./bin
OBJ=./obj
SRC=./src

SRC_FILE = $(wildcard $(SRC)/*.cpp)
OBJ_FILE = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILE))

DIRECTORY=bin obj include src data img
EXEC=main

all: prepare $(EXEC) imageGenerator

prepare: | $(DIRECTORY)

$(DIRECTORY): 
	mkdir -p $@
$(EXEC): $(OBJ_FILE)
	$(CC) -o $(BIN)/$@ $^ $(CCFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -o $@ -c $< $(CCFLAGS)

imageGenerator:
	g++ $(SRC)/ImageGenerator/imageGenerator.cpp -o $(BIN)/imageGenerator -I/usr/local/include  -L/usr/local/lib -lPNGwriter -lpng -lz -lfreetype -I/usr/include/freetype2

clean:
	rm -rf $(OBJ) $(LIB)
	rm -rf ./data
	rm -rf ./img

properclean: clean
	rm -rf $(BIN)
	rm -rf ./data
	rm -rf ./img


.PHONY: all prepare directory file clean properclean