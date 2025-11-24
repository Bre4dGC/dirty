CFLAGS = -Wall -Wextra -I"include/" -g
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin
TARGET = $(BIN_DIR)/dirty

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean build

all: build

build: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	cc $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@

install: $(TARGET)
	cp $(TARGET) /usr/local/bin

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
