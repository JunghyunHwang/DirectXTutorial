#include "VertexShader.h"
#include "GraphicsEngine.h"

void VertexShader::release()
{
	mVs->Release();
	delete this;
}

bool VertexShader::init(const void* shaderByteCode, size_t byteCodeSize)
{
	if (!SUCCEEDED(GraphicsEngine::getInstance()->mD3dDevice->CreateVertexShader(shaderByteCode, byteCodeSize, nullptr, &mVs)))
	{
		return false;
	}

	return true;
}
