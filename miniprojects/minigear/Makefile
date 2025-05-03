# Makefile for MiniGear emulator
CC = gcc
CFLAGS = -Wall -O2
TARGET = minigear

all: $(TARGET)

$(TARGET): minigear.c
	$(CC) $(CFLAGS) -o $(TARGET) minigear.c

clean:
	rm -f $(TARGET)
