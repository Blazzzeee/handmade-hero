#!/usr/bin/env bash

echo "Starting build phase"
set -euo pipefail

SRC="main.cpp"
DEBUG=${DEBUG:-0}
OUT_DIR="target"
BIN="$OUT_DIR/handmade.exe"

mkdir -p "$OUT_DIR"

if [ "$DEBUG" -eq 1 ]; then
    echo "Building DEBUG"
    x86_64-w64-mingw32-g++ \
        -O0 -g -Wall -Wextra \
        "$SRC" \
        -o "$BIN" \
        -lgdi32 -luser32
else
    echo "Building RELEASE"
    x86_64-w64-mingw32-g++ \
        -O2 -Wall -Wextra \
        "$SRC" \
        -o "$BIN" \
        -lgdi32 -luser32
fi

echo "Compilation Successful"

if [ "$DEBUG" -eq 0 ]; then
    echo "Running with Wine"
    wine "$BIN"
else
    echo "Running with winedbg (Wine debugger)"
    winedbg "$BIN"
fi
