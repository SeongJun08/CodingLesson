#pragma once
#include <list>
#include "Card.h"

namespace solitaire
{
	class Game
	{
		const int BOARD_ROW = 5;
		const int BOARD_COLUMN = 8;
		const Gdiplus::RectF BOARD_COUNT{ 850.0f, 60.0f, 120.0f, 30.0f };

	public:
		void Init(HWND hwnd);
		void Release();

		void Draw(Gdiplus::Graphics& graphics);
		void OnClick(int x, int y);

	private:
		HWND mHwnd;
		std::unique_ptr<Gdiplus::Image> mBackgroundImage;
		std::list<Card> mDeck;
		int mFlipCount;
		Card *mpSelectedCard;

		void CreateCardDeck();
	};
}


