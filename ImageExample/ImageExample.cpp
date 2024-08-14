#include <fstream>
#include <vector>
#include "ImageExample.h"

#pragma comment(lib, "WindowsCodecs.lib")

using namespace Microsoft::WRL;

HRESULT ImageExample::Init(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
	HRESULT hr = CoInitialize(nullptr);
	ThrowIfFailed(hr);

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(mspWICFactory.GetAddressOf())
	);
	ThrowIfFailed(hr);

	D2DFramework::Init(hInstance, title, width, height);
	
	//return LoadBMP(L"Images/32.bmp", mspBitmap.GetAddressOf());
	return LoadWICImage(L"Images/1.gif", mspBitmap.GetAddressOf());
}

void ImageExample::Render()
{
	mspRenderTarget->BeginDraw();

	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	if (mspBitmap)
	{
		mspRenderTarget->DrawBitmap(mspBitmap.Get());
	}

	HRESULT hr = mspRenderTarget->EndDraw();
	if (hr == D2DERR_RECREATE_TARGET)
	{
		CreateDeviceResources();
	}
}

void ImageExample::Release()
{
	D2DFramework::Release();

	mspBitmap.Reset();
	mspWICFactory.Reset();

	CoUninitialize();
}

HRESULT ImageExample::LoadBMP(LPCWSTR filename, ID2D1Bitmap **ppBitmap)
{
	// 1. BMP 파일 열기
	std::ifstream file;
	file.open(filename, std::ifstream::binary);

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	// 2. BITMAPFILEHEADER
	file.read((char *)&bfh, sizeof(BITMAPFILEHEADER));
	// 3. BITMAPINFOHEADER
	file.read((char *)&bih, sizeof(BITMAPINFOHEADER));

	if (bfh.bfType != 0x4D42)	// 424D
	{
		OutputDebugString(L"Wrong Bitmap File!!\n");
		return E_FAIL;
	}

	if (bih.biBitCount != 32)
	{
		OutputDebugString(L"RGBA format not found!!\n");
		return E_FAIL;
	}
	// 4. 픽셀 배열 찾아가기 (offset)
	file.seekg(bfh.bfOffBits);

	std::vector<unsigned char> pixels(bih.biSizeImage);

	// 5. 배열 읽기
	int pitch = bih.biWidth * (bih.biBitCount / 8);

	//file.read((char *)&pixels[0], bih.biSizeImage);

	/*for (int y = bih.biHeight - 1; y >= 0; y--)
	{
		file.read((char*)&pixels[y * pitch], pitch);
	}
	file.close();*/

	int index{};
	for (int y = bih.biHeight - 1; y >= 0; --y)
	{
		index = y * pitch;
		for (int x = 0; x < bih.biWidth; ++x)
		{
			unsigned char r{}, g{}, b{}, a{};
			file.read((char*)&b, 1);
			file.read((char*)&g, 1);
			file.read((char*)&r, 1);
			file.read((char*)&a, 1);

			if (r == 30 && g == 199 && b == 250)
			{
				r = g = b = a = 0;
			}

			pixels[index++] = b;
			pixels[index++] = g;
			pixels[index++] = r;
			pixels[index++] = a;
		}
	}

	file.close();

	// 6. ID2D1Bitmap 만들기
	HRESULT hr = mspRenderTarget->CreateBitmap(
		D2D1::SizeU(bih.biWidth, bih.biHeight),
		D2D1::BitmapProperties(
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, 
				D2D1_ALPHA_MODE_PREMULTIPLIED)
		),
		ppBitmap
	);
	ThrowIfFailed(hr);

	(*ppBitmap)->CopyFromMemory(
		nullptr,
		&pixels[0],
		pitch
	);
	return S_OK;
}

HRESULT ImageExample::LoadWICImage(LPCWSTR filename, ID2D1Bitmap **ppBitmap)
{
	//WIC
	// 1. 디코더 생성
	// 2. 디코더에서 프레임을 구해 옴
	// 3. 컨버터로 픽셀 변환
	// 4. IBitmap 생성
	ComPtr<IWICBitmapDecoder> bitmapDecoder;

	HRESULT hr{};

	hr = mspWICFactory->CreateDecoderFromFilename(
		filename,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		bitmapDecoder.GetAddressOf()
	);
	ThrowIfFailed(hr);
	
	ComPtr<IWICBitmapFrameDecode> frame;
	hr = bitmapDecoder->GetFrame(0, frame.GetAddressOf());
	ThrowIfFailed(hr);

	ComPtr<IWICFormatConverter> converter;
	hr = mspWICFactory->CreateFormatConverter(converter.GetAddressOf());
	ThrowIfFailed(hr);

	hr = converter->Initialize(
		frame.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0,
		WICBitmapPaletteTypeCustom
	);
	ThrowIfFailed(hr);

	hr = mspRenderTarget->CreateBitmapFromWicBitmap(
		converter.Get(), 
		mspBitmap.GetAddressOf()
	);
	ThrowIfFailed(hr);


	return S_OK;
}
