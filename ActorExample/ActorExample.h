#pragma once
#include <memory>
#include "D2DFramework.h"
#include "Actor.h"

class ActorExample : public D2DFramework
{
	std::unique_ptr<Actor> mspBackground;
	std::unique_ptr<Actor> mspBug;

public:
	HRESULT Init(HINSTANCE hInstance, LPCWSTR title = L"ActorExample", 
		UINT width = 1024, UINT height = 768) override;
	void Release() override;
	void Render() override;


};

