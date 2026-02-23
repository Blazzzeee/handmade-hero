#include <windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow) {
  MessageBox(0, "This is handmade hero", "Handmade hero",
             MB_OK | MB_ICONINFORMATION);
  return 0;
}
