#include "D3DFramework.h"
#include <sstream>

#pragma comment (lib, "d3d11.lib")

using namespace Microsoft::WRL;

void D3DFramework::Initialize(HINSTANCE hInstance, int width, int height)
{
	mScreenWidth = width;
	mScreenHeight = height;
	mbPaused = false;

	InitWindow(hInstance);
	InitD3D();
}

void D3DFramework::Destroy()
{
	mspSwapChain->SetFullscreenState(false, NULL);

	mspDepthStencilView.Reset();
	mspDepthStencil.Reset();
	mspRenderTargetView.Reset();
	mspRenderTarget.Reset();

	mspSwapChain.Reset();
	mspDevice.Reset();
	mspDeviceContext.Reset();

	DestroyWindow(mHwnd);
	UnregisterClass(CLASS_NAME.c_str(), mInstance);
}

void D3DFramework::GameLoop()
{
	mTimer.Start();
	mInput.Initialize();

	MSG msg{};
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
			mTimer.Update();
			
			if (mbPaused)
			{
				Sleep(100);
			}
			else
			{
				CalculateFPS();

				Update(mTimer.DeltaTime());
				RenderFrame();
			}
			// GAMELOP
			RenderFrame();
		}
	}
}

LRESULT D3DFramework::MessageHandle(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*D3DFramework *pFramework = reinterpret_cast<D3DFramework*>(
		GetWindowLongPtr(hwnd, GWLP_USERDATA) 필요없어짐
	);*/
	switch (message)
	{
		case WM_KEYDOWN:
			mInput.SetKeyDown(static_cast<unsigned int>(wParam));
			break;

		case WM_KEYUP:
			mInput.SetKeyUp(static_cast<unsigned int>(wParam));
			break;

		case WM_LBUTTONDOWN:
			mInput.SetKeyDown(VK_LBUTTON);
			break;

		case WM_LBUTTONUP:
			mInput.SetKeyUp(VK_LBUTTON);
			break;

		case WM_RBUTTONDOWN:
			mInput.SetKeyDown(VK_RBUTTON);
			break;

		case WM_RBUTTONUP:
			mInput.SetKeyUp(VK_RBUTTON);
			break;

		case WM_MOUSEMOVE:
			mInput.SetCursorPosition(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_ACTIVATE:
			if (LOWORD(wParam) == WA_INACTIVE)
			{
				mbPaused = true;
				mTimer.Stop();
			}
			else
			{
				mbPaused = false;
				mTimer.Resume();
			}
			break;

		case WM_PAINT:
			if (mResizing)
			{
				RenderFrame();
			}
			else
			{
				PAINTSTRUCT ps;
				BeginPaint(hwnd, &ps);
				EndPaint(hwnd, &ps);
			}
			break;

		case WM_ENTERSIZEMOVE:
			mTimer.Stop();
			mbPaused = true;
			mResizing = true;
			break;

		case WM_SIZE:
			mScreenWidth = LOWORD(lParam);
			mScreenHeight = HIWORD(lParam);

			if (mspDevice)
			{
				if (wParam == SIZE_MINIMIZED)
				{
					if (!mbPaused)
					{
						mTimer.Stop();
					}
					mbPaused = true;
					mMinimized = true;
					mMaximized = false;
				}
				else if (wParam == SIZE_MAXIMIZED)
				{
					mTimer.Resume();
					mbPaused = false;
					mMaximized = true;
					mMinimized = false;
					OnResize();
				}
				else if (wParam == SIZE_RESTORED)
				{
					if (mMinimized)
					{
						mTimer.Resume();
						mbPaused = false;
						mMinimized = false;
						OnResize();
					}
					else if (mMaximized)
					{
						mTimer.Resume();
						mbPaused = false;
						mMaximized = false;
						OnResize();
					}
					else if (mResizing)
					{

					}
					else
					{
						mTimer.Resume();
						mbPaused = false;
						OnResize();
					}
				}
			}
			break;

		case WM_EXITSIZEMOVE:
			mTimer.Resume();
			mbPaused = false;
			mResizing = false;
			OnResize();
			break;

		case WM_MENUCHAR:
			return MAKELRESULT(0, MNC_CLOSE);
			break;

		case WM_GETMINMAXINFO:
			((MINMAXINFO *)(lParam))->ptMinTrackSize.x = 640;
			((MINMAXINFO *)(lParam))->ptMinTrackSize.y = 480;
			break;

		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_ERASEBKGND:
			break;

		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

void D3DFramework::InitWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = CLASS_NAME.c_str();
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed to RegisterClassEx()", L"Error", MB_OK);
		return;
	}

	mInstance = hInstance;

	RECT wr{ 0,0,mScreenWidth, mScreenHeight };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	mTitleText = TITLE_TEXT;

	mHwnd = CreateWindowEx(
		0,
		CLASS_NAME.c_str(),
		TITLE_TEXT.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wr.right - wr.left, wr.bottom - wr.top,
		NULL, NULL,
		mInstance,
		NULL
	);

	if (!mHwnd)
	{
		MessageBox(nullptr, L"Failed to CreateWindowEx()", L"Error", MB_OK);
		return;
	}

	// static_cast
	// dynamic_cast 다형성 고려
	// A -> B 완전 서로 다른타입으로 reinterpret_cast
	SetWindowLongPtr(mHwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	ShowWindow(mHwnd, SW_SHOW);
	SetForegroundWindow(mHwnd);
	SetFocus(mHwnd);
	UpdateWindow(mHwnd);
}

void D3DFramework::InitD3D()
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = mScreenWidth;
	scd.BufferDesc.Height = mScreenHeight;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = mHwnd;
	scd.SampleDesc.Count = 1;
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&scd,
		mspSwapChain.ReleaseAndGetAddressOf(),
		mspDevice.ReleaseAndGetAddressOf(),
		NULL,
		mspDeviceContext.ReleaseAndGetAddressOf()
	);
	
	OnResize();
}

void D3DFramework::CalculateFPS()
{
	static int frameCount{};
	static float timeElapsed{};

	frameCount++;

	if (mTimer.TotalTime() - timeElapsed >= 1.0f)
	{
		float fps = static_cast<float>(frameCount);
		float mspf = 1000.0f / fps;

		std::wostringstream os;
		os.precision(5);
		os << mTitleText << L" - FPS: " << fps << ", Frame Time : " << mspf << "ms";

		SetWindowText(mHwnd, os.str().c_str());

		frameCount = 0;
		timeElapsed += 1.0f;
	}
}

void D3DFramework::OnResize()
{
	// 안전장치
	ID3D11RenderTargetView *nullViews[] = { nullptr };
	mspDeviceContext->OMSetRenderTargets(1, nullViews, nullptr);

	mspRenderTargetView.Reset();
	mspRenderTarget.Reset();
	mspDepthStencilView.Reset();
	mspDepthStencil.Reset();

	mspDeviceContext->Flush();

	//SwapChain 수정
	mspSwapChain->ResizeBuffers(
		0,
		mScreenWidth,
		mScreenHeight,
		DXGI_FORMAT_UNKNOWN,
		0
	);

	// RenderTarget
	mspSwapChain->GetBuffer(0, IID_PPV_ARGS(mspRenderTarget.ReleaseAndGetAddressOf()));
	mspDevice->CreateRenderTargetView(
		mspRenderTarget.Get(),
		nullptr,
		mspRenderTargetView.ReleaseAndGetAddressOf()
	);

	// DepthStencil
	CD3D11_TEXTURE2D_DESC td(
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		mScreenWidth,
		mScreenHeight,
		1,
		1,
		D3D11_BIND_DEPTH_STENCIL
	);
	mspDevice->CreateTexture2D(&td, nullptr, mspDepthStencil.ReleaseAndGetAddressOf());

	CD3D11_DEPTH_STENCIL_VIEW_DESC dsvd(
		D3D11_DSV_DIMENSION_TEXTURE2D
	);
	mspDevice->CreateDepthStencilView(
		mspDepthStencil.Get(),
		&dsvd,
		mspDepthStencilView.ReleaseAndGetAddressOf()
	);

	// 조립
	// Output Merger
	mspDeviceContext->OMSetRenderTargets(
		1,
		mspRenderTargetView.GetAddressOf(),
		mspDepthStencilView.Get()
	);

	// 뷰포트
	// Rasterizer Stage
	CD3D11_VIEWPORT viewport(0.0f, 0.0f, (float)mScreenWidth, (float)mScreenHeight);
	mspDeviceContext->RSSetViewports(1, &viewport);
}

void D3DFramework::RenderFrame()
{
	float bkgColor[]{ 0.0f, 0.2f, 0.4f, 1.0f };

	mspDeviceContext->ClearRenderTargetView(mspRenderTargetView.Get(), bkgColor);
	mspDeviceContext->ClearDepthStencilView(
		mspDepthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0
	);

	// 그리기
	Render();

	mspSwapChain->Present(0, 0);
}

// C함수 래핑
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	D3DFramework *pFramework = reinterpret_cast<D3DFramework *>(
		GetWindowLongPtr(hwnd, GWLP_USERDATA)
	);

	return pFramework->MessageHandle(hwnd, message, wParam, lParam);
}
