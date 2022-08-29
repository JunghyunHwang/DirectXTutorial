#pragma once
#include "d3d11.h"

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();
	bool load(void* listVertices, UINT sizeVertex, UINT sizeList, void* shaderByteCode, UINT sizeByteShader);
	bool release();
	UINT getSizeVertexList();
private:
	UINT mSizeVertex;
	UINT mSizeList;
	ID3D11Buffer* mBuffer;
	ID3D11InputLayout* mLayout;
private:
	friend class DeviceContext;
};

