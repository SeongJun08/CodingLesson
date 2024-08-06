#include "D2DFramework.h"

#pragma comment (lib, "d2d1.lib")

using namespace Microsoft::WRL;

HRESULT D2DFramework::Init(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
	InitWindow(hInstance, title, width, height);
	InitD2D();

	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);

	return S_OK;
}

void D2DFramework::Release()
{
	mpRenderTarget.Reset();
	mpD2DFactory.Reset();
}

void D2DFramework::Render()
{
	// 3. 그리기
	mpRenderTarget->BeginDraw();

	mpRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	HRESULT hr = mpRenderTarget->EndDraw();
	if (hr == D2DERR_RECREATE_TARGET)
	{
		CreateDeviceResources();
	}
}

int D2DFramework::GameLoop()
{
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			Render();
		}
	}

	return (int)msg.wParam;
}

HRESULT D2DFramework::InitWindow(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
	}

	RECT wr = { 0,0,(LONG)width,(LONG)height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hwnd = CreateWindowEx(
		NULL,
		CLASS_NAME,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wr.right - wr.left, wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd)
	{
		ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
	}

	mHwnd = hwnd;
	SetWindowLongPtr(mHwnd, GWLP_USERDATA, (LONG_PTR)this);

	return S_OK;
}

HRESULT D2DFramework::InitD2D()
{
	// 1. Factory 생성
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, mpD2DFactory.GetAddressOf());

	/*if (FAILED(hr))
	{
		OutputDebugString(L"failed to Create Factory!\n");
		return hr;
	}*/
	ThrowIfFailed(hr);

	return CreateDeviceResources();
}

HRESULT D2DFramework::CreateDeviceResources()
{
	// 2. 랜더타겟 생성
	RECT wr;
	GetClientRect(mHwnd, &wr);
	HRESULT hr = mpD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(mHwnd, D2D1::SizeU(wr.right - wr.left, wr.bottom - wr.top)),
		&mpRenderTarget
	);
	/*if (FAILED(hr))
	{
		OutputDebugString(L"Failed to Create Hwnd Render Target!");
		return hr;
	}*/
	ThrowIfFailed(hr);

	return S_OK;
}

LRESULT WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	D2DFramework* pFramework = (D2DFramework*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	switch (message)
	{
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
