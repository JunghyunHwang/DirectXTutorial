#include "SwapChain.h"
#include "GraphicsEngine.h"

bool SwapChain::init(HWND hWnd, UINT width, UINT height)
{
	GraphicsEngine* instance = GraphicsEngine::getInstance();
	ID3D11Device* device = instance->mD3dDevice;
	DXGI_SWAP_CHAIN_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hWnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = instance->mDxgiFactory->CreateSwapChain(device, &desc, &mSwapChain);

	if (FAILED(hr)) 
	{
		return false;
	}

	ID3D11Texture2D* buffer = NULL;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) &buffer);

	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &mRenderTargetView);
	buffer->Release();

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool SwapChain::release()
{
	mSwapChain->Release();
	delete this;
	return true;
}

bool SwapChain::present(bool vsync)
{
	mSwapChain->Present(vsync, NULL);

	return true;
}
