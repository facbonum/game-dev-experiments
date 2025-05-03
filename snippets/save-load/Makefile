# Simple Makefile for single-file snippet projects

PROJ = $(notdir $(CURDIR))
TARGET = $(PROJ)-test.exe
SRC = main.c

all:
	gcc $(SRC) -o $(TARGET) -I"C:/msys64/ucrt64/include/SDL2" -L"C:/msys64/ucrt64/lib" -lSDL2main -lSDL2 -mconsole

clean:
	del $(TARGET)
