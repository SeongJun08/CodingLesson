#include "Actor.h"

Actor::Actor(D2DFramework *pFramework, LPCWSTR filename) : 
    mpFramework(pFramework),
    mX(), mY(), mOpacity(1.0f)
{
    if (!pFramework)
    {
        ThrowIfFailed(E_INVALIDARG);
    }
    LoadWICImage(filename);
}

Actor::Actor(D2DFramework *pFramework, LPCWSTR filename, float x, float y, float opacity) :
    Actor(pFramework, filename)
{
    mX = x;
    mY = y;
    mOpacity = opacity;
}

Actor::~Actor()
{
    mspBitmap.Reset();
}

void Actor::Draw()
{
    Draw(mX, mY, mOpacity);
}

HRESULT Actor::LoadWICImage(LPCWSTR filename)
{
    Microsoft::WRL::ComPtr<IWICBitmapDecoder> bitmapDecoder;
    HRESULT hr;

    // 방어코드
    auto pFactory = mpFramework->GetWICFactory();
    if (!pFactory)
    {
        ThrowIfFailed(E_INVALIDARG);
    }

    hr = pFactory->CreateDecoderFromFilename(
        filename,
        nullptr,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        bitmapDecoder.GetAddressOf()
    );
    ThrowIfFailed(hr);

    Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
    ThrowIfFailed(bitmapDecoder->GetFrame(0, frame.GetAddressOf()));

    Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
    ThrowIfFailed(pFactory->CreateFormatConverter(converter.GetAddressOf()));

    hr = converter->Initialize(
        frame.Get(),
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        nullptr,
        0,
        WICBitmapPaletteTypeCustom
    );

    auto pRT = mpFramework->GetRenderTarget();
    if (!pRT)
    {
        ThrowIfFailed(E_INVALIDARG);
    }

    hr = pRT->CreateBitmapFromWicBitmap(
        converter.Get(),
        mspBitmap.ReleaseAndGetAddressOf()
    );
    ThrowIfFailed(hr);

    return S_OK;
}

void Actor::Draw(float x, float y, float opacity)
{
    auto size{ mspBitmap->GetPixelSize() };

    D2D1_RECT_F rct{
        x, y,
        (float)x + size.width,
        (float)y + size.height
    };

    mpFramework->GetRenderTarget()->DrawBitmap(
        mspBitmap.Get(),
        rct,
        opacity
        );
}
