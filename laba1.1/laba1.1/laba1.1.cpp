#include <windows.h>
#include <stdlib.h>

LRESULT CALLBACK WindProc(HWND hwmd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwmd, msg, wp, lp);
    }
}

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PWSTR args, int nCmdShow)
{
    //MessageBox(NULL, L"HELLO", "meafecd", MB_OK);
    
    const wchar_t CLASS_NAME[] = L"MyWindowClass";
    HWND hwmd;
    WNDCLASS wc = { };
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpfnWndProc = WindProc;
    wc.hInstance = hInst;
    wc.lpszClassName = CLASS_NAME;


    if (!RegisterClass(&wc))
        return -1;
    hwmd = CreateWindowEx(0,CLASS_NAME, L"FISICS", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInst, NULL);

/*   HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInst,  // Instance handle
        NULL        // Additional application data
    );
*/
    ShowWindow(hwmd, nCmdShow);
    MSG msg = { };
    while (GetMessage(&msg,NULL, NULL, NULL) )
    {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }
    return 0;
}

