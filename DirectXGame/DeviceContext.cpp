#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* mImmContext)
	:mDeviceContext(mImmContext)
{
}

void DeviceContext::clearRenderTargetColor(SwapChain* swapChain, float red, float green, float blue, float alpha)
{
	FLOAT clearColor[] = { red, green, blue, alpha };
	mDeviceContext->ClearRenderTargetView(swapChain->mRenderTargetView, clearColor);
	mDeviceContext->OMSetRenderTargets(1, &swapChain->mRenderTargetView, NULL);
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertexBuffer)
{
	UINT stride = vertexBuffer->mSizeVertex;
	UINT offset = 0;

	mDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->mBuffer, &stride, &offset);
	mDeviceContext->IASetInputLayout(vertexBuffer->mLayout);
}

void DeviceContext::drawTriangleList(UINT vertexCount, UINT startVertexIndex)
{
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mDeviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::drawTriangleStrip(UINT vertexCount, UINT startVertexIndex)
{
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	mDeviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = (FLOAT) width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	mDeviceContext->RSSetViewports(1, &vp);
}

bool DeviceContext::release()
{
	mDeviceContext->Release();
	delete this;

	return true;
}
