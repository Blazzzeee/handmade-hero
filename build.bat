@echo off

if not exist build mkdir build
pushd build

cl -Zi -nologo -W4 -WX -wd4201 -wd4100 -wd4189 ^
   -Od -MTd ^
   ..\main.cpp ^
   user32.lib gdi32.lib

popd
