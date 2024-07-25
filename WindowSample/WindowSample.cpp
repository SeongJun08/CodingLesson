#include <Windows.h>
#include <sstream>

// 윈도우 API 코딩 스타일
// 함수 : 파스칼 (단어의 시작을 대문자로)
// 변수 : 헝가리언 표기법 (변수의 타입 약자를 접두어로 붙임)

// int WinMain( p1, p2, p3, p4 )
// WINAPI : Windows Application Programming Interface
// _In_, _In_opt_, _Out_ : SAL (Sourcecode Annotation Language)
// HINSTANCE : Handle Of Instance  ( Pointer to Instance )
// LPSTR : Long Pointer Null-Terminated STRing

// 1. 윈도우 클래스 등록
// 2. 윈도우 생성
// 3. 윈도우 메세지 처리
// 4. 윈도우 프로시져 작성

const wchar_t MY_CLASS_NAME[]{ L"MyWindowClass" };

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,				// OS가 실행한 앱의 인스턴스 핸들
	_In_opt_ HINSTANCE hPrevInstance,		// 이전에 실행한 앱의 인스턴스 핸들
	_In_ LPSTR lpCmdLine,					// 명령줄 CommandLine 
	_In_ int nShowCmd						// Show Command
)
{
	//// HWND : Hanle of WiNDow 
	//// LPCTSTR : Long Pointer Constant Tchar STRing				Tchar : char-Asci, wchar-Unicode 둘 중에 필요한거로 가져다 쓰는거
	//// L 접두어 문자열 : Wide Character Literal
	//auto ret = MessageBox(nullptr, L"안녕하세요", L"SimpleWindow", MB_ICONEXCLAMATION | MB_YESNO);
	//if (ret == IDYES)
	//{
	//	MessageBox(nullptr, L"Yes", L"RESULT", MB_OK);
	//}
	//else if(ret == IDNO)
	//{
	//	MessageBox(nullptr, L"NO", L"RESULT", MB_OK);
	//}

	// 1. 윈도우 클래스 등록

	// WiNDow CLASS Extra
	WNDCLASSEX wc{};

	// 윈도우 API 구조체 반드시 0으로 초기화 필요
	// memset(&wc, 0, sizeof(WINDCLASSEX)); c언어 방법
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = MY_CLASS_NAME;		// long pointer to string zero-terminated
	wc.hInstance = hInstance;				// 중요
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_MENUTEXT;	// Handle of BRush Background
	wc.lpfnWndProc = WindowProc;				// 중요 : Long Pointer to FunctoiN WiNDow PROCedure
	wc.cbSize = sizeof(WNDCLASSEX);				// 중요 : Count of Bytes

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed to RegisterClassEx()", nullptr, MB_OK);
		return 0;
	}

	// 2. 윈도우 생성
	HWND hWnd;
	hWnd = CreateWindowEx(
		0,						// DWORD ExStyle	32비트 변수
		MY_CLASS_NAME,			// * 반드시 RegisterClassEx에서 사용한 이름
		L"Hello World",			// Window Name - 타이틀바
		WS_OVERLAPPEDWINDOW,	// 시스템버튼 유무 / 사이즈조절 / 스크롤바 etc
		0, 0,					// x좌표 y좌표 (윈도우는 좌상단이 0,0임) 
		600, 400,				// 가로 세로 길이
		NULL,					// Parent Window
		NULL,					// Menu
		hInstance,				// * 인스턴스
		NULL					// 추가 파라미터
	);
	if (!hWnd)
	{
		MessageBox(nullptr, L"Failed to CreateWindowEx()", nullptr, MB_OK);
		return 0;
	}

	ShowWindow(hWnd, nShowCmd);	// 26번줄 nShowCmd에서 받아옴
	UpdateWindow(hWnd);

	// 3. 메세지 처리
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))	// 메세지 큐에서 메세지 하나 꺼냄
	{
		TranslateMessage(&msg);				// 기계어로 된 데이터 -> 프로그래머 친화적
		DispatchMessage(&msg);				// Window Procedure Callback
	}

	// WM_QUIT이면 while이 종료
	return static_cast<int>(msg.wParam);
}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps{};
	HDC hdc = BeginPaint(hWnd, &ps);

	HBRUSH hatchBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));
	HBRUSH old = (HBRUSH)SelectObject(hdc, hatchBrush);
	Rectangle(hdc, 0, 0, 100, 100);
	DeleteObject(hatchBrush);
	SelectObject(hdc, old);

	HPEN bluePen = CreatePen(PS_DOT, 1, RGB(0, 0, 255));
	HPEN oldPen = (HPEN)SelectObject(hdc, bluePen);

	MoveToEx(hdc, 0, 110, nullptr);
	LineTo(hdc, 100, 110);

	DeleteObject(bluePen);
	SelectObject(hdc, oldPen);


	EndPaint(hWnd, &ps);
}
// 4. 윈도우 프로시져 정의
LRESULT WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
		case WM_LBUTTONDOWN:
		{
			//int x{};
			//int y{};

			//// lParam : | 상위 16 bit Y | 하위 16 X |
			//x = lParam & 0xffff;
			//y = lParam >> 16;

			//x = LOWORD(lParam);
			//y = HIWORD(lParam);

			//wchar_t buf[512];
			//wsprintf(buf, L"왼쪽 클릭 : %d, %d\n", x, y);
			//OutputDebugString(buf);

			HDC hdc{}; // Handle Of Device Context
			hdc = GetDC(hWnd);

			Rectangle(hdc, 0, 0, 100, 100);

			ReleaseDC(hWnd, hdc);


			break;
		}

		case WM_PAINT:
		{
			OnPaint(hWnd);

		}
			break;
		/*case WM_ERASEBKGND: break;*/

		case WM_KEYDOWN:
			if (wParam == VK_SPACE)
			{
				OutputDebugString(L"스페이스바!\n");
			}
			break;

		case WM_CLOSE:					// Window Message : CLOSE
			DestroyWindow(hWnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);			// WM_QUIT
			break;

		default:
			return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}

	return 0;
}
