#pragma once
#include "Actor.h"

class Bug : public Actor
{
	const D2D_POINT_2F UPVECTOR{ 0.0f, -1.0f };

public:
	Bug(D2DFramework *pFramework);
	virtual ~Bug();

	virtual void Draw() override;

	bool IsClicked(POINT &pt);

private:
	float mRotation;
	float mSteps;

};

