CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -loqs -lcrypto

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
TARGET_DIR = targets

#SRC = src/main.c src/sockets.c src/protocol.c
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

all: chat_app keygen

chat_app: $(TARGET_DIR)/main.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(TARGET_DIR)/main.c $(LDFLAGS)

keygen: $(TARGET_DIR)/keygen_main.c $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(TARGET_DIR)/keygen_main.c  $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
