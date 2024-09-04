#include <fstream>
#include <vector>
#include <d3dcompiler.h>
#include "TriangleSample.h"


#pragma comment (lib,"d3dcompiler.lib")

using namespace Microsoft::WRL;

// 0. 셰이더 준비
//		버텍스 셰이더, 픽셀 셰이더
//		컴파일

// 1. 파이프라인 설정
//		1-1. IA 설정
//			버텍스 구조 ( 좌표, 색상 ... )
//		1-2. 버텍스 셰이더, 픽셀 셰이더 커스텀 

// 2. 그리기
//		2-1. IA에 버텍스를 흘려 보냄

// 텍스쳐링
// 1. 버텍스 정보 변경
//		1-1. u, v 매핑 좌표
// 2. 텍스쳐 생성 (ID3D11Texture2D)
// 3. 이미지 로딩 - 복사
// 4. 텍스쳐 리소스 - 텍스쳐 리소스 뷰 (ShaderResourceView)
// 
// 5. 입력 레이아웃 변경
// 6. 파이프라인에 텍스쳐 제공

void TriangleSample::Initialize(HINSTANCE hInstance, int width, int height)
{
	D3DFramework::Initialize(hInstance, width, height);

	InitPipeline();
	InitTriangle();

	CreateTextureFromBMP();
}

void TriangleSample::Destroy()
{
	mspBlendState.Reset();
	mspSamplerState.Reset();
	mspTextureView.Reset();
	mspTexture.Reset();

	mspVertexBuffer.Reset();
	mspInputLayout.Reset();
	mspPixelShader.Reset();
	mspVertexShader.Reset();

	D3DFramework::Destroy();
}

void TriangleSample::Render()
{
	UINT stride{sizeof(VERTEX)};
	UINT offset{ 0 };
	mspDeviceContext->IASetVertexBuffers(
		0, 1, mspVertexBuffer.GetAddressOf(), &stride, &offset 
	);
	mspDeviceContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
	);

	mspDeviceContext->PSSetShaderResources(0, 1, mspTextureView.GetAddressOf());
	mspDeviceContext->PSGetSamplers(0, 1, mspSamplerState.GetAddressOf());
	mspDeviceContext->OMSetBlendState(mspBlendState.Get(), nullptr, 0xffffffff);
	mspDeviceContext->Draw(4, 0);
}

void TriangleSample::InitTriangle()
{
	// RAM - Stack
	VERTEX vertices[]{
		{ -0.5f, 0.5f, 0.0f, 0.0f, 0.0f },
		{ 0.5, 0.5, 0.0f, 1.0f, 0.0f },
		{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },
		{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f },
	};

	/* 사각형
	VERTEX vertices[]{
		{ -0.5f, 0.5f, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f } },
		{ 0.5f, 0.5f, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f } },
		{ -0.5f, -0.5f, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f } },
		{ 0.5f, -0.5f, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f} }
	};*/

	// VertexBuffer - GPU VRAM
	CD3D11_BUFFER_DESC bd(
		sizeof(vertices),
		D3D11_BIND_VERTEX_BUFFER,
		D3D11_USAGE_DYNAMIC,
		D3D11_CPU_ACCESS_WRITE
	);
	mspDevice->CreateBuffer(
		&bd, nullptr, mspVertexBuffer.ReleaseAndGetAddressOf()
	);

	// MAP/UNMAP
	D3D11_MAPPED_SUBRESOURCE ms;
	mspDeviceContext->Map(
		mspVertexBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&ms
	);
	memcpy(ms.pData, vertices, sizeof(vertices));
	mspDeviceContext->Unmap(mspVertexBuffer.Get(), 0);

	float border[4]{ 0.0f, 0.0f, 0.0f, 1.0f };
	CD3D11_SAMPLER_DESC sd(
		D3D11_FILTER_MIN_MAG_MIP_POINT,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		0.0f,
		1,
		D3D11_COMPARISON_ALWAYS,
		border,
		0,1 
	);
	mspDevice->CreateSamplerState(&sd, mspSamplerState.ReleaseAndGetAddressOf());

	D3D11_BLEND_DESC blend_desc;
	ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));

	blend_desc.RenderTarget[0].BlendEnable = true;
	blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	mspDevice->CreateBlendState(&blend_desc, mspBlendState.ReleaseAndGetAddressOf());

}

void TriangleSample::InitPipeline()
{
	//  Binary Large OBject 이진수로 된 데이터 묶음
	ComPtr<ID3DBlob> spVS;
	ComPtr<ID3DBlob> spPS;

	D3DCompileFromFile(
		L"VertexShader.hlsl",
		nullptr,
		nullptr,
		"main", 
		"vs_4_0_level_9_3",
		0, 0,
		spVS.GetAddressOf(),
		nullptr
	);

	D3DCompileFromFile(
		L"PixelShader.hlsl",
		nullptr,
		nullptr,
		"main",
		"ps_4_0_level_9_3",
		0, 0,
		spPS.GetAddressOf(),
		nullptr
	);

	// 셰이더 만들기
	mspDevice->CreateVertexShader(
		spVS->GetBufferPointer(),
		spVS->GetBufferSize(),
		nullptr,
		mspVertexShader.ReleaseAndGetAddressOf()
	);
	mspDevice->CreatePixelShader(
		spPS->GetBufferPointer(),
		spPS->GetBufferSize(),
		nullptr,
		mspPixelShader.ReleaseAndGetAddressOf()
	);

	// 파이프라인에 조립
	mspDeviceContext->VSSetShader(mspVertexShader.Get(), nullptr, 0);
	mspDeviceContext->PSSetShader(mspPixelShader.Get(), nullptr, 0);

	// Input Assembly
	D3D11_INPUT_ELEMENT_DESC ied[]
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, 
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,
			D3D11_INPUT_PER_VERTEX_DATA, 0
		}
	};

	mspDevice->CreateInputLayout(
		ied, 2, 
		spVS->GetBufferPointer(), spVS->GetBufferSize(),
		mspInputLayout.ReleaseAndGetAddressOf()
	);

	mspDeviceContext->IASetInputLayout(mspInputLayout.Get());

}

HRESULT TriangleSample::CreateTextureFromBMP()
{
	// 1. 파일 열기
	std::ifstream file;
	file.open("Images/32.bmp", std::ios::binary);

	BITMAPFILEHEADER bmh;
	BITMAPINFOHEADER bmi;

	// 2. BITMAPFILEHEADER 읽기
	file.read(reinterpret_cast<char *>(&bmh), sizeof(BITMAPFILEHEADER));
	// 3. BITMAPINFOGHEADER 읽기
	file.read(reinterpret_cast<char *>(&bmi), sizeof(BITMAPINFOHEADER));
	if (bmh.bfType != 0x4D42)
	{
		return E_FAIL;
	}
	if (bmi.biBitCount != 32)
	{
		return E_FAIL;
	}

	std::vector<char> pPixels(bmi.biSizeImage);
	// 4. 픽셀로 건너뛰기
	file.seekg(bmh.bfOffBits);
	// 5. 비트맵 읽기
	int pitch = bmi.biWidth * (bmi.biBitCount / 8);
	/*for (int y = bmi.biHeight - 1; y >= 0; --y)
	{
		file.read(&pPixels[y * pitch], pitch);
	}*/
	int index{};
	char r{}, g{}, b{}, a{};
	for (int y = bmi.biHeight - 1; y >= 0; --y)
	{
		index = y * pitch;

		for (int x = 0; x < bmi.biWidth; ++x)
		{
			file.read(&b, 1);
			file.read(&g, 1);
			file.read(&r, 1);
			file.read(&a, 1);

			if (static_cast<unsigned char>(r) == 30 &&
				static_cast<unsigned char>(g) == 199 &&
				static_cast<unsigned char>(b) == 250)
			{
				pPixels[index] = pPixels[index + 1] = pPixels[index + 2] = pPixels[index + 3] = 0;
			}
			else
			{
				pPixels[index] = b;
				pPixels[index+1] = g;
				pPixels[index+2] = r;
				pPixels[index+3] = a;

			}

			index += 4;
		}
	}

	file.close();

	CD3D11_TEXTURE2D_DESC td(
		DXGI_FORMAT_B8G8R8A8_UNORM,
		bmi.biWidth, bmi.biHeight,
		1, 1
	);

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &pPixels[0];
	initData.SysMemPitch = pitch;
	initData.SysMemSlicePitch = 0;

	mspDevice->CreateTexture2D(&td, &initData, mspTexture.ReleaseAndGetAddressOf());

	CD3D11_SHADER_RESOURCE_VIEW_DESC srvd(
		D3D11_SRV_DIMENSION_TEXTURE2D,
		td.Format,
		0,
		1
	);
	mspDevice->CreateShaderResourceView(mspTexture.Get(), &srvd, mspTextureView.ReleaseAndGetAddressOf());


	return S_OK;
}
