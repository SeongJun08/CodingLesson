#define WIN32_LEAN_AND_MEAM

#include <Windows.h>
#include <wrl/client.h>
#include <d3d11.h>

#pragma comment (lib, "d3d11.lib")

using namespace Microsoft::WRL;

const wchar_t CLASS_NAME[]{ L"MyClassName" };
const wchar_t TITLE_TEXT[]{ L"Direct3D Sample" };

int gScreenWidth{ 800 };
int gScreenHeight{ 600 };

HWND gHwnd{};
HINSTANCE gInstance{};

bool gMinimized{ false };
bool gMaximized{ false };
bool gResizing{ false };

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// Direct3D
// 1. 디바이스 생성 (디바이스 컨텍스트 포함) Device, Device Context(DC)
// 2. 스왑체인 생성
// 3. 렌더타겟으로 후면 버퍼를 지정
// 4. 깊이버퍼 + 스텐실버퍼 생성
// 5. 파이프라인 설정
// 6. 뷰포트 지정

// 7. 그리기
	// 렌더타겟
	// 깊이스텐실 버퍼

// 모드 스위치 룰
// 0. 해상도는 옵션으로 변경 - 변수
// 0. 윈도우 배경색 칠하기 과정을 생략
// 1. 스왑체인의 속성 변경
// 2. 게임 종료시에 반드시 전체화면 모드 해제 후 종료

// 가변 해상도
// 스왑체인
// 렌더타겟(렌더타겟 뷰)
// 깊이스텐실(깊이스텐실 뷰)
// 뷰포트

// 윈도우 창 크기 변경 메시지
// WM_SIZE, WM_ENTERSIZEMOVE, WM_EXITSIZEMOVE
// 크기 조절 제한, 메뉴 없음 사운드(띠리링) 소리 제거

ComPtr<ID3D11Device> gspDevice{};
ComPtr<ID3D11DeviceContext> gspDeviceContext;

ComPtr<IDXGISwapChain> gspSwapChain{}; // Interface DX GI(Graphic Infrastructure)
ComPtr<ID3D11Texture2D> gspRenderTarget{};
ComPtr<ID3D11Texture2D> gspDepthStencil{};
ComPtr<ID3D11RenderTargetView> gspRenderTargetView;
ComPtr<ID3D11DepthStencilView> gspDepthStencilView{};


void InitD3D();
void OnResize();
void DestroyD3D();
void Render();

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed to RegisterClassEx()", L"Error", MB_OK);
		return 0;
	}

	gInstance = hInstance;

	RECT wr{ 0,0,gScreenWidth, gScreenHeight };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	gHwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		TITLE_TEXT,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wr.right - wr.left, wr.bottom - wr.top,
		NULL, NULL,
		gInstance, 
		NULL
	);

	if (!gHwnd)
	{
		MessageBox(nullptr, L"Failed to CreateWindowEx()", L"Error", MB_OK);
		return 0;
	}

	ShowWindow(gHwnd, nShowCmd);
	SetForegroundWindow(gHwnd);
	SetFocus(gHwnd);
	UpdateWindow(gHwnd);

	InitD3D();

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
			// GAMELOP
			Render();
		}
	}

	DestroyD3D();

	return (int)msg.wParam;
}

LRESULT WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
			if (gResizing)
			{
				Render();
			}
			else
			{
				PAINTSTRUCT ps;
				BeginPaint(hwnd, &ps);
				EndPaint(hwnd, &ps);
			}
			break;

		case WM_ENTERSIZEMOVE:
			gResizing = true;
			break;

		case WM_SIZE:
			gScreenWidth = LOWORD(lParam);
			gScreenHeight = HIWORD(lParam);

			if (gspDevice)
			{
				if (wParam == SIZE_MINIMIZED)
				{
					gMinimized = true;
					gMaximized = false;
				}
				else if (wParam == SIZE_MAXIMIZED)
				{
					gMaximized = true;
					gMinimized = false;
					OnResize();
				}
				else if (wParam == SIZE_RESTORED)
				{
					if (gMinimized)
					{
						gMinimized = false;
						OnResize();
					}
					else if (gMaximized)
					{
						gMaximized = false;
						OnResize();
					}
					else if (gResizing)
					{

					}
					else
					{
						OnResize();
					}
				}
			}
			break;

		case WM_EXITSIZEMOVE:
			gResizing = false;
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

void InitD3D()
{
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = gScreenWidth;
	scd.BufferDesc.Height = gScreenHeight;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = gHwnd;
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
		gspSwapChain.ReleaseAndGetAddressOf(),
		gspDevice.ReleaseAndGetAddressOf(),
		NULL,
		gspDeviceContext.ReleaseAndGetAddressOf()
	);

	OnResize();
}

void OnResize()
{
	// 안전장치
	ID3D11RenderTargetView *nullViews[] = { nullptr };
	gspDeviceContext->OMSetRenderTargets(1, nullViews, nullptr);

	gspRenderTargetView.Reset();
	gspRenderTarget.Reset();
	gspDepthStencilView.Reset();
	gspDepthStencil.Reset();

	gspDeviceContext->Flush();

	//SwapChain 수정
	gspSwapChain->ResizeBuffers(
		0,
		gScreenWidth,
		gScreenHeight,
		DXGI_FORMAT_UNKNOWN,
		0
	);

	// RenderTarget
	gspSwapChain->GetBuffer(0, IID_PPV_ARGS(gspRenderTarget.ReleaseAndGetAddressOf()));
	gspDevice->CreateRenderTargetView(
		gspRenderTarget.Get(),
		nullptr,
		gspRenderTargetView.ReleaseAndGetAddressOf()
	);

	// DepthStencil
	CD3D11_TEXTURE2D_DESC td(
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		gScreenWidth,
		gScreenHeight,
		1,
		1,
		D3D11_BIND_DEPTH_STENCIL
	);
	gspDevice->CreateTexture2D(&td, nullptr, gspDepthStencil.ReleaseAndGetAddressOf());

	CD3D11_DEPTH_STENCIL_VIEW_DESC dsvd(
		D3D11_DSV_DIMENSION_TEXTURE2D
	);
	gspDevice->CreateDepthStencilView(
		gspDepthStencil.Get(),
		&dsvd,
		gspDepthStencilView.ReleaseAndGetAddressOf()
	);

	// 조립
	// Output Merger
	gspDeviceContext->OMSetRenderTargets(
		1,
		gspRenderTargetView.GetAddressOf(),
		gspDepthStencilView.Get()
	);

	// 뷰포트
	// Rasterizer Stage
	CD3D11_VIEWPORT viewport(0.0f, 0.0f, (float)gScreenWidth, (float)gScreenHeight);
	gspDeviceContext->RSSetViewports(1, &viewport);
}

void DestroyD3D()
{
	gspSwapChain->SetFullscreenState(false, NULL);

	gspDepthStencilView.Reset();
	gspDepthStencil.Reset();
	gspRenderTargetView.Reset();
	gspRenderTarget.Reset();

	gspSwapChain.Reset();
	gspDevice.Reset();
	gspDeviceContext.Reset();

	DestroyWindow(gHwnd);
	UnregisterClass(CLASS_NAME, gInstance);
}

void Render()
{
	float bkgColor[] { 0.0f, 0.2f, 0.4f, 1.0f };

	gspDeviceContext->ClearRenderTargetView(gspRenderTargetView.Get(), bkgColor);
	gspDeviceContext->ClearDepthStencilView(
		gspDepthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0
	);

	// 그리기

	gspSwapChain->Present(0, 0);
}
