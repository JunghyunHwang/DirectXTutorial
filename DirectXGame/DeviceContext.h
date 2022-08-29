#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* mImmContext);
	void clearRenderTargetColor(SwapChain* swapChain, float red, float green, float blue, float alpha);
	void setVertexBuffer(VertexBuffer* vertexBuffer);
	void drawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void drawTriangleStrip(UINT vertexCount, UINT startVertexIndex);
	void setViewportSize(UINT width, UINT height);

	bool release();
private:
	ID3D11DeviceContext* mDeviceContext;
private:
	friend class VertexBuffer;
};

