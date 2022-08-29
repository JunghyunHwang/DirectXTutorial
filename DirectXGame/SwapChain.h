#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	bool init(HWND hWnd, UINT width, UINT height);
	bool release();
	bool present(bool vsync);
private:
	friend class DeviceContext;
private:
	IDXGISwapChain* mSwapChain;
	ID3D11RenderTargetView* mRenderTargetView;
};

