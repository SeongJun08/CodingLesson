#include "Game.h"

#pragma comment (lib, "Gdiplus.lib")

const wchar_t gClassName[] = L"MyWindowClass";

LRESULT CALLBACK WindowProc(
    HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam
);

// TEST
solitaire::Game gGame;

int WINAPI WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = gClassName;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpfnWndProc = WindowProc;
    wc.cbSize = sizeof(WNDCLASSEX);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(
            nullptr, L"Failed to register window class!", L"Error",
            MB_ICONEXCLAMATION | MB_OK
        );
        return 0;
    }

    RECT wr = { 0, 0, 1024, 768 };

    AdjustWindowRect(&wr, WS_OVERLAPPED | WS_SYSMENU, FALSE);
    hWnd = CreateWindowEx(NULL,
        gClassName,
        L"Solitaire Game",
        WS_OVERLAPPED|WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        wr.right - wr.left,
        wr.bottom - wr.top,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (hWnd == nullptr)
    {
        MessageBox(
            nullptr, L"Failed to create window class!", L"Error",
            MB_ICONEXCLAMATION | MB_OK
        );
        return 0;
    }

    // 초기화
    gGame.Init(hWnd);

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 해제
    gGame.Release();

    Gdiplus::GdiplusShutdown(gdiplusToken);
    return static_cast<int>(msg.wParam);
}

void OnPaint(HWND hwnd)
{
    HDC hdc;
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);
    Gdiplus::Graphics graphics(hdc);

    gGame.Draw(graphics);

    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WindowProc(
    HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam
)
{
    switch (message)
    {
        case WM_PAINT:
            OnPaint(hwnd);
            break;

        case WM_LBUTTONUP:
            gGame.OnClick(LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
