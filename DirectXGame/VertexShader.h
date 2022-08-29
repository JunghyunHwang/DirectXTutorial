#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class VertexShader
{
public:
	void release();
private:
	bool init(const void* shaderByteCode, size_t byteCodeSize);
private:
	ID3D11VertexShader* mVs;
private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};

