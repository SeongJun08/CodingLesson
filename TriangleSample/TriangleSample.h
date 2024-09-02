#pragma once

#include "D3DFramework.h"

class TriangleSample : public D3DFramework
{
public:
	void Initialize(HINSTANCE hInstance, int width = 800, int height = 600) override;
	void Destroy() override;

protected:
	void Render() override;

private:
	void InitTriangle();
	void InitPipeline();

	struct VERTEX
	{
		FLOAT X, Y, Z;
		FLOAT Color[4];
	};

	Microsoft::WRL::ComPtr<ID3D11VertexShader> mspVertextShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mspPixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>mspInputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mspVertextBuffer;
	// 버텍스 버퍼, 인덱스 버퍼

};

