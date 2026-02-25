#include <windows.h>
#include <winuser.h>
 
LRESULT MainWindowProcedure(
  HWND WindowHandle,
  UINT msg,
  WPARAM WParam,
  LPARAM LParam)
{

    LRESULT res  = 0;
    switch(msg){
        case(WM_ACTIVATEAPP):
            {
                res = 0;
            } break;
        case(WM_CLOSE):
            {
                res = 0;
            } break;
        case(WM_MOVE):
            {
                res = 0;
            } break;
        case(WM_SIZE):
            {
                res = 0;
            } break;
        default :
            {
            return DefWindowProcA(WindowHandle,msg,WParam,LParam);
            } break;
    }
  
  return res;
}
 
 
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance , LPSTR lpCmdLine, int nCmdShow) {
 
  // MessageBox(0, "This is handmade hero", "Handmade hero",
  //            MB_OK | MB_ICONINFORMATION);
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;
 
    // create a window class  
    WNDCLASSA window_class = {0};

    window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = MainWindowProcedure;
    window_class.hInstance = hInstance;
    window_class.lpszClassName = "Handmade";

    if(!RegisterClassA(&window_class)){
      return 1;
    }

    // Finally create a window 
    HWND window_handle = CreateWindowExA(
    0,
    window_class.lpszClassName,
    "Handmade Hero",
    WS_VISIBLE | WS_OVERLAPPEDWINDOW, 
    CW_USEDEFAULT ,
    CW_USEDEFAULT ,
    CW_USEDEFAULT ,
    CW_USEDEFAULT ,
    NULL,
    NULL ,
    hInstance,
    (void *) NULL ); 


    if (!window_handle){
        return 1;
    }


    // TODO: handle message queue 
    MSG msg;
    while (GetMessage(&msg , window_handle, 0 , 0)){
        TranslateMessage(&msg); 
        DispatchMessage(&msg);
    }

    
    return 0;
 
}
