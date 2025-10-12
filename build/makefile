ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE = .exe
    PATHSEP = \\
else
    RM = rm -f
    EXE =
    PATHSEP = /
endif

# Compiler and flags
CXX := g++
SFMLLD := -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s \
          -lfreetype -lpng -lz -lbrotlidec -lbrotlicommon -lharfbuzz \
          -lopengl32 -lwinmm -lgdi32 -ljpeg -lvorbisenc -lvorbis -lvorbisfile \
          -logg -lflac -lbz2 -lgraphite2 -lrpcrt4 -ldwrite

LDFLAGS := $(SFMLLD) -lmpfr -lgmp -static -static-libgcc -static-libstdc++

# Base flags
BASE_CXXFLAGS := 	-I../include -I ../include/gui -I ../include/gui/elements \
									-I../include/eval -I../include/eval/tokenizer -I C:/msys64/ucrt64/include \
					-Wall -Wextra -std=c++26 -MMD -MP -static -static-libgcc -static-libstdc++

# Release/Debug
CXXFLAGS := $(BASE_CXXFLAGS) -O0
DEBUGFLAGS := $(BASE_CXXFLAGS) -ggdb

# Directories (relative to ./build/)
SRC_DIRS := ../src ../src/gui ../src/gui/elements ../src/evaluate ../src/evaluate/tokenizer
OBJ_DIR := obj
BIN_DIR := .

# Files
SOURCES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJECTS := $(patsubst ../src/%.cpp,$(OBJ_DIR)/%.o,$(wildcard ../src/*.cpp)) \
           $(patsubst ../src/gui/%.cpp,$(OBJ_DIR)/gui_%.o,$(wildcard ../src/gui/*.cpp)) \
           $(patsubst ../src/gui/elements/%.cpp,$(OBJ_DIR)/gui_elements_%.o,$(wildcard ../src/gui/elements/*.cpp)) \
           $(patsubst ../src/eval/%.cpp,$(OBJ_DIR)/eval_%.o,$(wildcard ../src/eval/*.cpp)) \
           $(patsubst ../src/eval/tokenizer/%.cpp,$(OBJ_DIR)/eval_tokenizer_%.o,$(wildcard ../src/eval/tokenizer/*.cpp))
DEPENDS := $(OBJECTS:.o=.d)   # corresponding .d files

EXECUTABLE := $(BIN_DIR)/calcflex2$(EXE)

# Default target
all: build

build: CXXFLAGS := $(CXXFLAGS)
build: $(EXECUTABLE)

debug: CXXFLAGS := $(DEBUGFLAGS)
debug: $(EXECUTABLE)

# Link objects into executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile files in ../src
$(OBJ_DIR)/%.o: ../src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile files in ../src/gui
$(OBJ_DIR)/gui_%.o: ../src/gui/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile files in ../src/gui/elements
$(OBJ_DIR)/gui_elements_%.o: ../src/gui/elements/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile files in ../src/evaluate
$(OBJ_DIR)/eval_%.o: ../src/eval/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile files in ../src/evaluate/tokenizer
$(OBJ_DIR)/eval_tokenizer_%.o: ../src/eval/tokenizer/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure obj dir exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f obj/*.o $(EXECUTABLE)

build-run: build
	./$(EXECUTABLE)

debug-run: debug
	gdb $(EXECUTABLE)

.PHONY: all clean build build-run debug debug-run

-include $(DEPENDS)
