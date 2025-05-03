PROJ := $(notdir $(CURDIR))
OUT := $(PROJ)-test.exe

CC := gcc
CFLAGS := -I"C:/msys64/ucrt64/include/SDL2" -I"./include"
LDFLAGS := -L"C:/msys64/ucrt64/lib" -lSDL2main -lSDL2 -lSDL2_ttf

# Specify source files
SRC := src/main.c src/ball.c src/paddle.c src/power_up.c src/score.c src/score_display.c

# Object files corresponding to the source files
OBJ := $(SRC:src/%.c=build/%.o)

# The default target
all: $(OUT)

# Linking object files to produce the executable
$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Compile the .c files into .o object files
build/%.o: src/%.c | build/
	$(CC) -c $< -o $@ $(CFLAGS)

# Create the build directory if it doesn't exist
build/:
	mkdir build

# Clean up the build artifacts (Windows-style)
clean:
	-del $(OUT)
	-del /Q build\*.o 2>nul || exit 0
