BUILD_DIR := build
EXECUTABLE := $(BUILD_DIR)/bin/main

all: build run

configure:
	@echo "[BUILD LOGS]: Configuring CMake"
	cmake -B $(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build: configure
	@echo "[BUILD LOGS]: Building using CMake"
	cmake --build $(BUILD_DIR)

run: build
	@echo "[BUILD LOGS]: Running main"
	@$(EXECUTABLE)

clean:
	@echo "[BUILD LOGS]: Cleaning build directory"
	rm -rf $(BUILD_DIR)

.PHONY: all configure build run clean
