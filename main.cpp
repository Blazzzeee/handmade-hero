#include <windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow) {
  MessageBoxA(0, "Hello from Handmade Hero setup!", "Success", MB_OK);
  return 0;
}
