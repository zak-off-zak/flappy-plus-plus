#!/bin/bash

echo "[BUILD LOGS]: Building using Cmake"
cmake -B build
cmake --build build

echo "[BUILD LOGS]: Running main"
./build/bin/main
