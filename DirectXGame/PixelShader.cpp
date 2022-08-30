#include <cassert>

#include "PixelShader.h"
#include "GraphicsEngine.h"

void PixelShader::release()
{
	mPixelShader->Release();
	delete this;
}

bool PixelShader::init(const void* shaderByteCode, size_t byteCodeSize)
{
	if (!SUCCEEDED(GraphicsEngine::getInstance()->mD3dDevice->CreatePixelShader(shaderByteCode, byteCodeSize, nullptr, &mPixelShader)))
	{
		assert(false);
		return false;
	}

	return true;
}
