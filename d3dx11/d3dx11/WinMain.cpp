#include "Window.h"

int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,   // string holding command line inputs
    int       nCmdShow)    // shows window
{
    Window wnd(800, 480, L"saffcon");

    // message pump
    MSG msg;
    BOOL gResult;

    while((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)

    {
        TranslateMessage(&msg);   // process message, posts WM_CHAR to msg queue if keydown detected
        DispatchMessage(&msg);    // pass message to windowproc
    }

    // process gResult
    // -1 if error, 0 if quit, stays in loop above if >0
    if (gResult == -1)
    {
        return -1;
    }

    return static_cast<int>(msg.wParam); // return quit code
}
