CC := gcc
CFLAGS := -Iinclude -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable # TODO: use Wall only
LDFLAGS :=
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
LOG_DIR := logs
TARGET := $(BIN_DIR)/run
LAUNCH_SCRIPT := launch_game.sh

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all clean directories launch_script

# Add 'directories' and 'launch_script' as a prerequisite to the 'all' target
all: directories launch_script $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	@echo "#######################"
	@echo "Linking $@"
	@echo "#######################"
	$(CC) $(LDFLAGS) -o $@ $^

# Add a rule for creating necessary directories
directories: $(BIN_DIR) $(OBJ_DIR) $(LOG_DIR)
$(BIN_DIR) $(OBJ_DIR) $(LOG_DIR):
	@echo "#######################"
	@echo "Creating directory $@"
	@echo "#######################"
	mkdir -p $@

# Rule for creating the launch script
launch_script:
	@echo "#!/bin/bash" > $(LAUNCH_SCRIPT)
	@echo "" >> $(LAUNCH_SCRIPT)
	@echo "cd \"bin\"" >> $(LAUNCH_SCRIPT)
	@echo "" >> $(LAUNCH_SCRIPT)
	@echo "./run" >> $(LAUNCH_SCRIPT)
	@chmod +x $(LAUNCH_SCRIPT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo ""
	@echo "#######################"
	@echo "Compiling $<"
	@echo "#######################"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "#######################"
	@echo "Cleaning up"
	@echo "#######################"
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LOG_DIR) $(LAUNCH_SCRIPT)