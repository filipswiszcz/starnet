CC = clang
CFLAGS = -std=c99
LDFLAGS = -Llib -lglfw -framework Cocoa -framework OpenGL -framework IOKit

BUILD_DIR = build
SRC_DIR = src
LIB_DIR = lib

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = $(BUILD_DIR)/starnet

run: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: ${SRC_DIR}/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*