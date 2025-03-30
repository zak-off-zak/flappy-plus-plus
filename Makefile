BUILD_DIR := build
EXECUTABLE := $(BUILD_DIR)/bin/main
ASSETS_DIR := assets

all: build run

configure:
	@echo "[BUILD LOGS]: Configuring CMake"
	cmake -B $(BUILD_DIR) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

debug_conf:
	cmake -B $(BUILD_DIR) -D CMAKE_BUILD_TYPE=Debug

build: configure
	@echo "[BUILD LOGS]: Building using CMake"
	cmake --build $(BUILD_DIR)
	cp -r $(ASSETS_DIR) ~ # Copying the assets to the home dicrectory to enbale a smooth run when the game is run by double clicking on it in the finder

run: build
	@echo "[BUILD LOGS]: Running main"
	@$(EXECUTABLE)

wipe_assets:
	rm -rf  ~/$(ASSETS_DIR)

clean: wipe_assets
	@echo "[BUILD LOGS]: Cleaning build directory"
	rm -rf $(BUILD_DIR)

.PHONY: all configure build run clean wipe_assets debug_conf
