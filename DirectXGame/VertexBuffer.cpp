#include "VertexBuffer.h"
#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer()
	: mLayout(0)
	, mBuffer(0)
{

}

bool VertexBuffer::load(void* listVertices, UINT sizeVertex, UINT sizeList, void* shaderByteCode, UINT sizeByteShader)
{
	if (mBuffer)
	{
		mBuffer->Release();
	}

	if (mLayout)
	{
		mLayout->Release();
	}

	D3D11_BUFFER_DESC buffDesc = {};
	buffDesc.Usage = D3D11_USAGE_DEFAULT;
	buffDesc.ByteWidth = sizeVertex * sizeList;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = listVertices;

	mSizeVertex = sizeVertex;
	mSizeList = sizeList;

	if (FAILED(GraphicsEngine::getInstance()->mD3dDevice->CreateBuffer(&buffDesc, &initData, &mBuffer)))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },


	};

	UINT sizeLayout = ARRAYSIZE(layout);

	if (FAILED(GraphicsEngine::getInstance()->mD3dDevice->CreateInputLayout(layout, sizeLayout, shaderByteCode, sizeByteShader, &mLayout)))
	{
		return false;
	}

	return true;
}

bool VertexBuffer::release()
{
	mLayout->Release();
	mBuffer->Release();
	delete this;

	return true;
}

UINT VertexBuffer::getSizeVertexList()
{
	return mSizeList;
}
