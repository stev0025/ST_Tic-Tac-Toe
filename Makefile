CC := gcc
CFLAGS := -Iinclude -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable
LDFLAGS :=
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
TARGET := $(BIN_DIR)/run

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	@echo "#######################"
	@echo "Linking $@"
	@echo "#######################"
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN_DIR):
	@echo ""
	@echo "#######################"
	@echo "Creating directory $@"
	@echo "#######################"
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo ""
	@echo "#######################"
	@echo "Compiling $<"
	@echo "#######################"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@echo ""
	@echo "#######################"
	@echo "Creating directory $@"
	@echo "#######################"
	mkdir -p $@

clean:
	@echo "#######################"
	@echo "Cleaning up"
	@echo "#######################"
	rm -rf $(OBJ_DIR) $(BIN_DIR)