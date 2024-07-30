#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include <memory>
#include <string>

namespace solitaire
{
	class Card
	{
	public:
		enum class Type
		{
			Wolf,
			Dragon,
			Bear
		};

	private:
		std::unique_ptr<Gdiplus::Image> mBackImage;
		std::unique_ptr<Gdiplus::Image> mFrontImage;

		HWND mHwnd;
		int mX;
		int mY;
		Type mType;
		bool mIsFront;
		int mIndex;

	public:
		Card(HWND hwnd, int index, Type type, int x, int y);

		void Draw(Gdiplus::Graphics& graphics);
		void Flip(bool isFront);
		bool CheckClicked(int x, int y);
		void Invalidate();

		Type GetType() { return mType; }
		int GetIndex() { return mIndex; }
	};

}
