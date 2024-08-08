#include <Windows.h>
#include "VirtualVideo.h"

VirtualVideo myFramework;

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	int ret{};

	try
	{
		myFramework.Init(hInstance);

		ret = myFramework.GameLoop();

		myFramework.Release();
	}
	catch (const com_exception &e)
	{
		OutputDebugStringA(e.what());
	}

	return ret;

	/*int ret{};

	myFramework.Init(hInstance);

	ret = myFramework.GameLoop();

	myFramework.Release();
	
	return ret;*/
}


