#include "BuggyHouse.h"

HRESULT BuggyHouse::Init(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
	HRESULT hr = D2DFramework::Init(hInstance, title, width, height);
	ThrowIfFailed(hr);

	mspBackground = std::make_unique<Actor>(this, L"Images/back1_1024.png");

	float sx{}, sy{};
	RECT rct;
	GetClientRect(mHwnd, &rct);

	for (int i = 0; i < 40; ++i)
	{
		sx = (float)(rand() % (rct.right - rct.left));
		sy = (float)(rand() % (rct.bottom - rct.top));

		mBugs.push_back(
			std::make_shared<Actor>(this, L"Images/bug1_1.png", sx, sy)
		);
	}
	
	return S_OK;
}

void BuggyHouse::Release()
{
	for (auto &bug : mBugs)
	{
		bug.reset();
	}
	mBugs.clear();

	mspBackground.reset();

	D2DFramework::Release();
}

void BuggyHouse::Render()
{
	mspRenderTarget->BeginDraw();

	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	mspBackground->Draw();
	for (auto &bug : mBugs)
	{
		auto pos = bug->Getposition();
		pos.x += (float)(1 - rand() % 3);
		pos.y += (float)(1 - rand() % 3);
		bug->SetPosition(pos);

		bug->Draw();


	}

	HRESULT hr = mspRenderTarget->EndDraw();
	if (hr == D2DERR_RECREATE_TARGET)
	{
		CreateDeviceResources();
	}
}
