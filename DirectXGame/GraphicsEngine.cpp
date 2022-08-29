#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	HRESULT res;

	for (int i = 0; i < numDriverTypes; ++i)
	{
		res = D3D11CreateDevice(NULL, driverTypes[i], NULL, NULL, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &mD3dDevice
			, &mFeatureLevel, &mImmContext);

		if (SUCCEEDED(res))
		{
			mD3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**) &mDxgiDevice);
			mDxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**) &mDxgiAdapter);
			mDxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&mDxgiFactory);

			mImmDeviceContext = new DeviceContext(mImmContext);

			return true;
		}
	}

	return false;
}

bool GraphicsEngine::release()
{
	mDxgiDevice->Release();
	mDxgiAdapter->Release();
	mDxgiFactory->Release();

	mImmDeviceContext->release();
	mD3dDevice->Release();

	return true;
}

GraphicsEngine* GraphicsEngine::getInstance()
{
	static GraphicsEngine engine;
	return &engine;
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return mImmDeviceContext;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

bool GraphicsEngine::createShaders()
{
	ID3DBlob* errblob = nullptr;

	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &mVertexShaderBlob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &mPixelShaderBlob, &errblob);

	mD3dDevice->CreateVertexShader(mVertexShaderBlob->GetBufferPointer(), mVertexShaderBlob->GetBufferSize(), nullptr, &mVertexShader);
	mD3dDevice->CreatePixelShader(mPixelShaderBlob->GetBufferPointer(), mPixelShaderBlob->GetBufferSize(), nullptr, &mPixelShader);

	return true;
}

bool GraphicsEngine::setShader()
{
	mImmContext->VSSetShader(mVertexShader, nullptr, 0);
	mImmContext->PSSetShader(mPixelShader, nullptr, 0);

	return true;
}

void GraphicsEngine::getShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = mVertexShaderBlob->GetBufferPointer();
	*size = (UINT)mVertexShaderBlob->GetBufferSize();
}
