CC = gcc
CFLAGS = -Wall -Wextra -g -pedantic -Wunused-but-set-variable -std=c11 -I "include/"
LDFLAGS = "C:/msys64/mingw64/include/PDCurses/wincon/pdcurses.a" -lpdcurses -L/path/to/cjson/lib -lcjson

SRC = src/main.c \
	  src/ui.c \
	  src/operations.c \
	  src/operations/dir_ops.c \
	  src/operations/processes.c \
	  src/operations/file_ops.c \
	  src/operations/clipboard.c \
	  src/operations/commands.c \
	  src/ui/panels.c \
	  src/ui/input.c \
	  src/utils/config.c \
	  src/utils/hotkeys_parser.c \
	  src/utils/cfg_parser.c
OBJ = $(SRC:src/%.c=build/%.o)
TARGET = bin/dotFile.exe

# Create necessary directories
DIRECTORIES = bin $(sort $(dir $(OBJ)))

all: directories $(TARGET)

directories:
	@echo Creating directories...
	@for %%d in ($(subst /,\,$(DIRECTORIES))) do ( \
		if not exist "%%d" mkdir "%%d" \
	)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q build\*.o
	del /Q build\operations\*.o
	del /Q build\ui\*.o
	del /Q build\utils\*.o
	del $(TARGET)

run: all
	.\$(TARGET)