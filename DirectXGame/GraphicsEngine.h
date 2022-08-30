#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class VertexShader;
class PixelShader;

class GraphicsEngine
{
public:
	bool init();
	bool release();

	static GraphicsEngine* getInstance();
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	VertexBuffer* createVertexBuffer();

public:
	VertexShader* createVertexShader(const void* shaderByteCode, size_t byteCodeSize);
	PixelShader* createPixelShader(const void* shaderByteCode, size_t byteCodeSize);
	bool compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	bool compilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void releaseCompiledShader();

private:
	ID3D11Device* mD3dDevice; // 기능 지원 점검과 자원 할당에 사용
	D3D_FEATURE_LEVEL mFeatureLevel;
	IDXGIDevice* mDxgiDevice;
	IDXGIAdapter* mDxgiAdapter;
	IDXGIFactory* mDxgiFactory;
	ID3D11DeviceContext* mImmContext;
	DeviceContext* mImmDeviceContext;

private:
	ID3DBlob* mBlob = nullptr;
	ID3DBlob* mVertexShaderBlob = nullptr;
	ID3DBlob* mPixelShaderBlob = nullptr;
	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;

private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class VertexShader;
	friend class PixelShader;
};
