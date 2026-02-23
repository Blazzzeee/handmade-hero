@echo off
setlocal

REM Load Visual Studio Developer Environment
call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" -arch=x64 -host_arch=x64

if errorlevel 1 (
    echo Failed to initialize MSVC environment.
    exit /b 1
)

if not exist build mkdir build
pushd build

cl -Zi -nologo -W4 -Od ^
   ..\main.cpp ^
   user32.lib gdi32.lib

popd
echo Build complete.
