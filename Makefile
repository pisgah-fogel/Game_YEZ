# Makefile to build YEZ Game
# Can be called directly

default_target: all

.PHONY : default_target

# You can ajust the following to your system's specifications
SHELL = /bin/bash
CMAKE_COMMAND = /usr/bin/cmake
ARGS = -DDEBUG -Wall -g
OPT = 

all: main.o RessourcesManager.o Log.o
	g++ $(OPT) build/*.o -lsfml-graphics -lsfml-window -lsfml-system -o YEZ

main.o:
	if [ -d build ]; then echo ""; else mkdir build; fi
	g++ $(ARGS) -c src/main.cpp -o build/main.o

RessourcesManager.o:
	g++ $(ARGS) -c src/RessourcesManager.cpp -o build/RessourcesManager.o

Log.o:
	g++ $(ARGS) -c src/Log.cpp -o build/Log.o

clean:
	rm -r build
	rm YEZ


.PHONY : all
