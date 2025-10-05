# Compiler and flags
CXX := g++
SFMLLD := -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lfreetype -lpng -lz -lbrotlidec -lbrotlicommon -lharfbuzz -lopengl32 -lwinmm -lgdi32 -ljpeg -lvorbisenc -lvorbis -lvorbisfile -logg -lflac -lbz2 -lgraphite2 -lrpcrt4 -ldwrite
LDFLAGS := $(SFMLLD) -lgmp -lmpfr -static -static-libgcc -static-libstdc++
CXXFLAGS := -I../include -I ../include/gui -Wall -Wextra -std=c++26 -MMD -MP -static -static-libgcc -static-libstdc++

# Directories (relative to ./build/)
SRC_DIRS := ../src ../src/gui
OBJ_DIR := obj
BIN_DIR := .

# Files
SOURCES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJECTS := $(patsubst ../src/%.cpp,$(OBJ_DIR)/%.o,$(wildcard ../src/*.cpp)) \
           $(patsubst ../src/gui/%.cpp,$(OBJ_DIR)/gui_%.o,$(wildcard ../src/gui/*.cpp))
DEPENDS := $(OBJECTS:.o=.d)   # corresponding .d files
EXECUTABLE := $(BIN_DIR)/calcflex2.exe

# Default target
all: build

build: $(EXECUTABLE)
	echo $(SOURCES)

# Link objects into executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile files in ../src
$(OBJ_DIR)/%.o: ../src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile files in ../src/gui
$(OBJ_DIR)/gui_%.o: ../src/gui/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure obj dir exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean build artifacts
clean:
	if exist obj\*.o del /Q obj\*.o
	if exist calcflex2.exe del /Q calcflex2.exe

build-run: build
	./$(EXECUTABLE)

.PHONY: all clean build-run build

-include $(DEPENDS)