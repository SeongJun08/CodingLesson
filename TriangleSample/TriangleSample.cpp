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

void TriangleSample::Initialize(HINSTANCE hInstance, int width, int height)
{
	D3DFramework::Initialize(hInstance, width, height);

	InitPipeline();
	InitTriangle();
}

void TriangleSample::Destroy()
{
	mspVertextBuffer.Reset();
	mspInputLayout.Reset();
	mspPixelShader.Reset();
	mspVertextShader.Reset();

	D3DFramework::Destroy();
}

void TriangleSample::Render()
{
	UINT stride{sizeof(VERTEX)};
	UINT offset{ 0 };
	mspDeviceContext->IASetVertexBuffers(
		0, 1, mspVertextBuffer.GetAddressOf(), &stride, &offset 
	);
	mspDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	mspDeviceContext->Draw(4, 0);
}

void TriangleSample::InitTriangle()
{
	// RAM - Stack
	VERTEX vertices[]{
		{ -0.5f, 0.5f, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f } },
		{ 0.5f, 0.5f, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f } },
		{ -0.5f, -0.5f, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f } },
		{ 0.5f, -0.5f, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f} }
	};

	/* 사각형
	VERTEX vertices[]{
		{ -0.5f, 0.5f, 0.0f, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ 0.5f, -0.5f, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ -0.5f, -0.5f, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f } },
		{ 0.5f, 0.5f, 0.0f, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ 0.5f, -0.5f, 0.0f, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ -0.5f, 0.5f, 0.0f, { 1.0f, 0.0f, 0.0f, 1.0f } }
	};*/

	// VertexBuffer - GPU VRAM
	CD3D11_BUFFER_DESC bd(
		sizeof(vertices),
		D3D11_BIND_VERTEX_BUFFER,
		D3D11_USAGE_DYNAMIC,
		D3D11_CPU_ACCESS_WRITE
	);
	mspDevice->CreateBuffer(
		&bd, nullptr, mspVertextBuffer.ReleaseAndGetAddressOf()
	);

	// MAP/UNMAP
	D3D11_MAPPED_SUBRESOURCE ms;
	mspDeviceContext->Map(
		mspVertextBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&ms
	);
	memcpy(ms.pData, vertices, sizeof(vertices));
	mspDeviceContext->Unmap(mspVertextBuffer.Get(), 0);
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
		mspVertextShader.ReleaseAndGetAddressOf()
	);
	mspDevice->CreatePixelShader(
		spPS->GetBufferPointer(),
		spPS->GetBufferSize(),
		nullptr,
		mspPixelShader.ReleaseAndGetAddressOf()
	);

	// 파이프라인에 조립
	mspDeviceContext->VSSetShader(mspVertextShader.Get(), nullptr, 0);
	mspDeviceContext->PSSetShader(mspPixelShader.Get(), nullptr, 0);

	// Input Assembly
	D3D11_INPUT_ELEMENT_DESC ied[]
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, 
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		{
			"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
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
