#!/usr/bin/env bash

echo "Starting build phase"
set -euo pipefail
SRC="main.cpp"
DEBUG=${DEBUG:-0}
BIN=target/obj.exe

x86_64-w64-mingw32-gcc -O2 -Wall -Wextra -g -o "$BIN" $SRC $()

echo "Compilation Successfull"

if [ "$DEBUG" -eq 0 ]; then
    echo "Starting server without debugger"
    wine ./"$BIN"
else
    echo "Starting server inside gdb"
    gdb --args ./"$BIN"
fi
