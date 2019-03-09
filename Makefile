# Get operating system info
UNAME := $(shell uname)

# ---------------
# Variables

# Compiler
C = g++

# Compiler flags
CFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic -Wfloat-equal

# Path to dependency files
DEP = -Idep

# Graphics cpp files
GF = src/gfx/*.cpp

# Graphics header files
GH = src/gfx/*.h

# Path to graphics header files
GHPATH = -Isrc/gfx

# Logic cpp files
LF = src/logic/*.cpp

# Game logic headers
LH = src/logic/*.h

# Path to game logic header files
LHPATH = -Isrc/logic

# Flags to link in the SDL2 and SDL2_ttf libraries
# Detect if macOS or Linux and adjust syntax accordingly
ifeq ($(UNAME), Darwin)
LIBS = -framework SDL2 -framework SDL2_ttf
endif
ifeq ($(UNAME), Linux)
# Flags to link in the SDL2 and SDL2_ttf frameworks
LIBS = -lSDL2 -lSDL2_ttf
endif

# Path to main function - the game entry point
MAIN = src/main.cpp

# All Unit test files
TF = test/*.cpp

# The framework used in automated unit testing of game logic
TFW = dep/catch.hpp

# ---------------
# Targets

# By default, recompile the game if any changes and then immediately run it
all: gamec play

# Recompile the game if there are any changes
gamec: $(MAIN) $(LH) $(LF) $(GH) $(GF)
	$(C) $(MAIN) $(LF) $(GF) -o bin/game $(LHPATH) $(GHPATH) $(LIBS) $(CFLAGS)

# Run the game
play:
	./bin/game

# Recompile unit tests if any changes and then run them all
test: testc testrun

# Recompile all unit tests if there are any changes
testc: $(TF) $(TFW) $(LH) $(LF)
	$(C) $(TF) $(LF) -o bin/tst $(DEP) $(LHPATH) $(CFLAGS)

# Run all automated unit tests on the game logic
testrun:
	./bin/tst

# Delete all files created during compilation or gameplay
clean:
	rm -f bin/*
