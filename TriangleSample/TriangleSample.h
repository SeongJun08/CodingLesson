#pragma once

#include <DirectXMath.h>
#include "D3DFramework.h"

class TriangleSample : public D3DFramework
{
public:
	void Initialize(HINSTANCE hInstance, int width = 800, int height = 600) override;
	void Destroy() override;

protected:
	void Update(float delta) override;
	void Render() override;

private:
	void InitTriangle();
	void InitPipeline();

	HRESULT CreateTextureFromBMP();

	struct VERTEX
	{
		float X, Y, Z;
		float U, V;
	};

	struct MatrixBuffer
	{
		DirectX::XMMATRIX world;
	};
	
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mspVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mspPixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mspInputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mspVertexBuffer;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> mspTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mspTextureView;// 버텍스 버퍼, 인덱스 버퍼
	Microsoft::WRL::ComPtr<ID3D11SamplerState> mspSamplerState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> mspBlendState;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mspConstantBuffer;

	float mX, mY;
	float mRotationZ;
	DirectX::XMMATRIX mWorld;

};

