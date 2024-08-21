#pragma once

#include <memory>
#include <list>
#include "D2DFramework.h"
#include "Actor.h"
#include "Bug.h"

class BuggyHouse : public D2DFramework
{
    std::unique_ptr<Actor> mspBackground;
    std::list<std::shared_ptr<Bug>> mBugs;

public:
    HRESULT Init(HINSTANCE hInstance,
        LPCWSTR title = L"BuggyHouse",
        UINT width = 1024, UINT height = 768) override;

    virtual void Release() override;
    virtual void Render() override;

    void CheckBugs();

};
