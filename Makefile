# Makefile for your project

CC = gcc
CFLAGS = -g -Wall -Wextra -Iinclude -Werror -Wpedantic

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Corresponding object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
# Binary executable
TARGET = $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm -pthread

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory
$(shell mkdir -p $(BUILD_DIR))

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

# Phony target to avoid conflicts with files named "all" or "clean"
.PHONY: all clean
