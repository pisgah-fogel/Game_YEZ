# Makefile to build YEZ Game
# Can be called directly

default_target: all

.PHONY : default_target

# You can ajust the following to your system's specifications
SHELL = /bin/bash
CMAKE_COMMAND = /usr/bin/cmake

all: main.o
	g++ build/main.o -lsfml-graphics -lsfml-window -lsfml-system -o YEZ

main.o:
	if [ -d build ]; then echo ""; else mkdir build; fi
	cd build
	g++ -c main.cpp -o build/main.o

	cd ..

clean:
	rm -r build
	rm YEZ


.PHONY : all
