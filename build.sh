#!/usr/bin/env bash

echo "Starting build phase"
set -euo pipefail

SRC="main.cpp"
DEBUG=${DEBUG:-0}
OUT_DIR="target"
BIN="$OUT_DIR/handmade.exe"

mkdir -p "$OUT_DIR"

build() {
    local mode="$1"

    local CXX="x86_64-w64-mingw32-g++"
    local CXXFLAGS="-Wall -Wextra"
    local LDFLAGS="-lgdi32 -luser32"

    if [ "$mode" = "debug" ]; then
        echo "Building DEBUG"
        CXXFLAGS="$CXXFLAGS -O0 -g"
    else
        echo "Building RELEASE"
        CXXFLAGS="$CXXFLAGS -O2"
    fi

    $CXX $CXXFLAGS "$SRC" -o "$BIN" $LDFLAGS
}

if [ "$DEBUG" -eq 1 ]; then
    build debug
else
    build release
fi

echo "Compilation Successful"

if [ "$DEBUG" -eq 0 ]; then
    echo "Running with Wine"
    wine "$BIN"
else
    echo "Running with gdb + Wine"
    winedbg --gdb "$BIN"
 fi
