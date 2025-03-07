CC = gcc
CFLAGS = -Wall -Wextra -g -pedantic -std=c11
LDFLAGS = "include/PDcurses/wincon/pdcurses.a" -lpdcurses

SRC  = src/main.c src/ui.c src/navigation.c src/file_ops.c src/clipboard.c src/commands.c src/hotkeys.c src/config.c
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = bin\dotFile.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-del /Q build\*.o
	-del $(TARGET)

run: all
	./$(TARGET)