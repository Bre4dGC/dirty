CC = gcc
CFLAGS = -Wall -Wextra -g -pedantic -std=c11 -I "include/"
LDFLAGS = -lpdcurses

SRC = src/main.c \
	  src/ui.c \
	  src/operations/dir_ops.c \
	  src/operations/hotkeys.c \
	  src/operations/processes.c \
	  src/operations/file_ops.c \
	  src/operations/clipboard.c \
	  src/operations/commands.c \
	  src/ui/panels.c \
	  src/ui/navigation.c \
	  src/utils/config.c \
	  src/utils/cfg_parser.c
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = bin/dotFile.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-del /Q build\*.o
	-del $(TARGET)

run: all
	.\$(TARGET)