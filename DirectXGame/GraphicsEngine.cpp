#include <d3dcompiler.h>
#include <cassert>

#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

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
			break;
		}
	}

	if (FAILED(res))
	{
		return false;
	}

	mImmDeviceContext = new DeviceContext(mImmContext);

	mD3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&mDxgiDevice);
	mDxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&mDxgiAdapter);
	mDxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&mDxgiFactory);

	return true;
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

VertexShader* GraphicsEngine::createVertexShader(const void* shaderByteCode, size_t byteCodeSize)
{
	VertexShader* vs = new VertexShader();

	if (!vs->init(shaderByteCode, byteCodeSize))
	{
		vs->release();
		return nullptr;
	}

	return vs;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shaderByteCode, size_t byteCodeSize)
{
	PixelShader* ps = new PixelShader();

	if (!ps->init(shaderByteCode, byteCodeSize))
	{
		ps->release();
		assert(false);
		return nullptr;
	}

	return ps;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize)
{
	ID3DBlob* errorBlob = nullptr;

	if (!SUCCEEDED(D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "vs_5_0", 0, 0, &mBlob, &errorBlob)))
	{
		if (errorBlob)
		{
			errorBlob->Release();

		}

		return false;
	}

	*shaderByteCode = mBlob->GetBufferPointer();
	*byteCodeSize = mBlob->GetBufferSize();

	return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize)
{
	ID3DBlob* errorBlob = nullptr;

	if (!SUCCEEDED(D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "ps_5_0", 0, 0, &mBlob, &errorBlob)))
	{
		if (errorBlob)
		{
			errorBlob->Release();

		}

		return false;
	}

	*shaderByteCode = mBlob->GetBufferPointer();
	*byteCodeSize = mBlob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseCompiledShader()
{
	if (mBlob)
	{
		mBlob->Release();
	}
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
