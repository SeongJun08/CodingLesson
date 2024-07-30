#include "Card.h"

using namespace solitaire;

Card::Card(HWND hwnd, int index, Type type, int x, int y) :
	mHwnd(hwnd), mIndex(index), mX(x), mY(y), mType(type), mIsFront(false)
{
	mBackImage = std::make_unique<Gdiplus::Image>(L"images/card_back.png");

	std::wstring filename;
	switch (type)
	{
		case Type::Wolf:
			filename = L"images/card_creature_wolf.png";
			break;
		case Type::Dragon:
			filename = L"images/card_creature_dragon.png";
			break;
		case Type::Bear:
			filename = L"images/card_creature_bear.png";
			break; 
	}

	mFrontImage = std::make_unique<Gdiplus::Image>(filename.c_str());
}

void Card::Draw(Gdiplus::Graphics &graphics)
{
	if (mIsFront)
	{
		graphics.DrawImage(
			mFrontImage.get(), mX, mY, mFrontImage->GetWidth(), mFrontImage->GetHeight()
		);
	}
	else
	{
		graphics.DrawImage(
			mBackImage.get(), mX, mY, mBackImage->GetWidth(), mBackImage->GetHeight()
		);
	}
}

void Card::Flip(bool isFront)
{
	mIsFront = isFront;
	Invalidate();
}

bool Card::CheckClicked(int x, int y)
{
	if (x >= mX && y >= mY &&
		x <= mX + (int)mBackImage->GetWidth() &&
		y <= mY + (int)mBackImage->GetHeight())
	{
		Flip(!mIsFront);
		return true;
	}

	return false;
}

void solitaire::Card::Invalidate()
{
	RECT rct{ mX, mY, mX + (int)mBackImage->GetWidth(), mY + (int)mBackImage->GetHeight()};
	InvalidateRect(mHwnd, &rct, false);
}
