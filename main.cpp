#include <debugapi.h>
#include <windef.h>
#include <windows.h>
#include <wingdi.h>
#include <winuser.h>

#define persist static
#define global static
#define internal static

#define GetCoordinates(rectangle)                                    \
    x = (rectangle).left;                                            \
    y = (rectangle).top;                                             \
    width = (rectangle).right - (rectangle).left;                    \
    height = (rectangle).bottom - (rectangle).top;

global bool RUNNING;
global BITMAPINFO BitmapInfo;
global void *BitmapMemory;
global HBITMAP BitmapHandle;
global HDC BitmapDeviceContext;

internal void Win32ResizeDIBSection(int width, int height) {

    if (BitmapMemory) {
        DeleteObject(BitmapMemory);
    }

    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = width;
    BitmapInfo.bmiHeader.biHeight = height;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;
    BitmapInfo.bmiHeader.biSizeImage = NULL;

    BitmapHandle =
        CreateDIBSection(BitmapDeviceContext, &BitmapInfo,
                         DIB_RGB_COLORS, &BitmapMemory, 0, 0);
}

internal void Win32UpdateWindow(HDC DeviceContext, int x, int y,
                                int width, int height) {

    StretchDIBits(DeviceContext, x, y, width, height, x, y, width,
                  height, BitmapMemory, &BitmapInfo, DIB_RGB_COLORS,
                  SRCCOPY);
}

internal LRESULT MainWindowProcedure(HWND WindowHandle, UINT msg,
                                     WPARAM WParam, LPARAM LParam) {

    LRESULT res = 0;
    switch (msg) {
    case (WM_ACTIVATEAPP): {
        res = 0;
    } break;
    case (WM_CLOSE): {
        RUNNING = false;
        // DestroyWindow(WindowHandle);
        OutputDebugStringA("WM_CLOSE");
    } break;
    case (WM_DESTROY): {
        RUNNING = false;
        // PostQuitMessage(0);
    } break;
    case (WM_MOVE): {
    } break;
    case (WM_SIZE): {
        int x, y, height, width;
        OutputDebugStringA("WM_SIZE");
        RECT client_rectangle;
        GetClientRect(WindowHandle, &client_rectangle);

        // convert rectangle into coordinates
        GetCoordinates(client_rectangle);
        Win32ResizeDIBSection(width, height);
    } break;
    case (WM_PAINT): {
        PAINTSTRUCT paint_info;
        HDC DeviceContext = BeginPaint(WindowHandle, &paint_info);
        if (!DeviceContext) {
            // ig we should call the def process , assuming we
            // cant process this req by the WM
            return DefWindowProcA(WindowHandle, msg, WParam, LParam);
        }

        int x, y, width, height;
        RECT rect = paint_info.rcPaint;

        GetCoordinates(rect);

        Win32UpdateWindow(DeviceContext, x, y, width, height);

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

    int ret;

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
    RUNNING = true;
    while (RUNNING) {
        if (GetMessage(&msg, window_handle, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // Unknown error
            PostQuitMessage(0);
            break;
        }
    }

    return 0;
}
