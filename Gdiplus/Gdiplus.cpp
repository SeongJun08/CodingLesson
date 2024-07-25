#include <Windows.h>					// 기본으로 들어감
#include <gdiplus.h>					// 기본아님, 추가 기능임, 선언포함
#pragma comment (lib, "Gdiplus.lib")	// 정의포함

using namespace Gdiplus;

const wchar_t CLASSNAME[]{ L"MyGDIPlusWindow" };

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	Gdiplus::GdiplusStartupInput gsi;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gsi, nullptr);

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = CLASSNAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Faild to RegisterClassEx().", L"Error", MB_OK);
		return 0;
	}

	RECT wr{ 0,0,640,480 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);

	HWND hWnd;
	hWnd = CreateWindowEx(
		NULL,
		CLASSNAME,
		L"Gdi + Sample",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(nullptr, L"Failed to CreateWindowEx()", L"Error", MB_OK);
		return 0;
	}
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	// Gdiplus = GDI를 클래스 C++ 화
	Graphics graphics(hdc);
	Pen redPen(Color(255, 255, 0, 0));
	SolidBrush whiteBrush(Color(255, 255, 255, 255));
	graphics.FillRectangle(&whiteBrush, 0, 0, 100, 100);

	graphics.DrawLine(&redPen, 0, 110, 100, 110);

	Image image(L"pocket.png");
	graphics.DrawImage(&image, 110, 110, 200, 200);

	EndPaint(hWnd, &ps);
}

LRESULT WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
			OnPaint(hWnd);
			break;

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
