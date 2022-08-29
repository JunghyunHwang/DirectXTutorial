#include "AppWindow.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
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
		{ -0.5f, -0.5f, 0.0f },
		{ -0.5f, 0.5f, 0.0f },
		{ 0.5f, -0.5f, 0.0f },
		{ 0.5f, 0.5f, 0.0f },
	};

	UINT sizeList = ARRAYSIZE(list);

	mVertexBuffer = instance->createVertexBuffer();

	instance->createShaders();

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	instance->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	mVertexShader = instance->createVertexShader(shaderByteCode, sizeShader);

	mVertexBuffer->load(list, sizeof(vertex), sizeList, shaderByteCode, sizeShader);

	instance->releaseCompiledShader();
}

void AppWindow::onUpdate()
{
	GraphicsEngine* instance = GraphicsEngine::getInstance();
	instance->getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, 0, 0.3f, 0.4f, 1);

	RECT rc = getClientWindowRect();
	instance->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	instance->setShader();
	instance->getImmediateDeviceContext()->setVertexShader(mVertexShader);
	instance->getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);

	instance->getImmediateDeviceContext()->drawTriangleStrip(mVertexBuffer->getSizeVertexList(), 0);
	mSwapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	mVertexBuffer->release();
	mSwapChain->release();
	GraphicsEngine::getInstance()->release();
}
