#include <windows.h>
#include <wingdi.h>
#include <winuser.h>

#define persist static
#define global static
#define internal static

internal LRESULT MainWindowProcedure(HWND WindowHandle, UINT msg,
                                     WPARAM WParam, LPARAM LParam) {

    LRESULT res = 0;
    switch (msg) {
    case (WM_ACTIVATEAPP): {
        res = 0;
    } break;
    case (WM_CLOSE): {
    } break;
    case (WM_MOVE): {
    } break;
    case (WM_SIZE): {
    } break;
    case (WM_PAINT): {
        PAINTSTRUCT paint_info;
        HDC DeviceContext = BeginPaint(WindowHandle, &paint_info);
        if (!DeviceContext) {
            // ig we should call the def process , assuming we cant
            // process this req by the WM
            return DefWindowProcA(WindowHandle, msg, WParam, LParam);
        }

        int x, y, width, height;

        x = paint_info.rcPaint.left;
        y = paint_info.rcPaint.top;

        width = paint_info.rcPaint.right - paint_info.rcPaint.left;
        height = paint_info.rcPaint.bottom - paint_info.rcPaint.top;
        if (!PatBlt(DeviceContext, x, y, width, height, BLACKNESS)) {
            return DefWindowProcA(WindowHandle, msg, WParam, LParam);
        }

        EndPaint(WindowHandle, &paint_info);
    } break;
    default: {
        return DefWindowProcA(WindowHandle, msg, WParam, LParam);
    } break;
    }

    return res;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow) {

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

    if (!RegisterClassA(&window_class)) {
        return 1;
    }

    // Finally create a window
    HWND window_handle = CreateWindowExA(
        0, window_class.lpszClassName, "Handmade Hero",
        WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
        hInstance, (void *)NULL);

    if (!window_handle) {
        return 1;
    }

    // TODO: handle message queue
    MSG msg;
    while (GetMessage(&msg, window_handle, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
