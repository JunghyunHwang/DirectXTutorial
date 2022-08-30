#include "AppWindow.h"

struct vec3
{
	float x;
	float y;
	float z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	GraphicsEngine* instance = GraphicsEngine::getInstance();

	instance->init();

	RECT rc = getClientWindowRect();
	mSwapChain = instance->createSwapChain();
	mSwapChain->init(mHwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		//X - Y - Z
		{ -0.5f, -0.5f, 0.0f, 0, 0, 0 }, // POS1
		{ -0.5f, 0.5f, 0.0f, 1, 1, 0 }, // POS2
		{ 0.5f, -0.5f, 0.0f, 0, 0, 1 }, // POS2
		{ 0.5f, 0.5f, 0.0f, 1, 1, 1 }
	};

	UINT sizeList = ARRAYSIZE(list);

	mVertexBuffer = instance->createVertexBuffer();

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	instance->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	mVertexShader = instance->createVertexShader(shaderByteCode, sizeShader);

	mVertexBuffer->load(list, sizeof(vertex), sizeList, shaderByteCode, sizeShader);

	instance->releaseCompiledShader();

	instance->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	mPixelShader = instance->createPixelShader(shaderByteCode, sizeShader);
	instance->releaseCompiledShader();
}

void AppWindow::onUpdate()
{
	GraphicsEngine* instance = GraphicsEngine::getInstance();
	// Clear the render target
	instance->getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, 0, 0.3f, 0.4f, 1);

	// Set viewport of render target in which we have to draw
	RECT rc = getClientWindowRect();
	instance->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	// Set default shader in the graphics pipeline to be able to draw
	instance->getImmediateDeviceContext()->setVertexShader(mVertexShader);
	instance->getImmediateDeviceContext()->setPixelShader(mPixelShader);

	// Set the vertices of the triangle to draw
	instance->getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);

	// Finally draw the triangle
	instance->getImmediateDeviceContext()->drawTriangleStrip(mVertexBuffer->getSizeVertexList(), 0);
	mSwapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	mVertexBuffer->release();
	mSwapChain->release();
	mVertexShader->release();
	mPixelShader->release();

	GraphicsEngine::getInstance()->release();
}
