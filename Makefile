CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -loqs -lcrypto

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

#SRC = src/main.c src/sockets.c src/protocol.c
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

TARGET = chat_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean