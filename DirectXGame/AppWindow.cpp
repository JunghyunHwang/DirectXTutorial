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
	mSwapChain = instance->createSwapChain();

	RECT rc = getClientWindowRect();
	mSwapChain->init(mHwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		{ -0.5f, -0.5f, 0.0f },
		{ -0.5f, 0.5f, 0.0f },
		{ 0.5f, -0.5f, 0.0f },
		{ 0.5f, 0.5f, 0.0f },
	};

	UINT sizeList = ARRAYSIZE(list);

	mVb = instance->createVertexBuffer();

	instance->createShaders();

	void* shaderByteCode = nullptr;
	UINT sizeShader = 0;
	instance->getShaderBufferAndSize(&shaderByteCode, &sizeShader);

	mVb->load(list, sizeof(vertex), sizeList, shaderByteCode, sizeShader);
}

void AppWindow::onUpdate()
{
	GraphicsEngine* instance = GraphicsEngine::getInstance();
	instance->getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, 0, 0.3f, 0.4f, 1);

	RECT rc = getClientWindowRect();
	instance->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	instance->setShader();
	
	instance->getImmediateDeviceContext()->setVertexBuffer(mVb);

	instance->getImmediateDeviceContext()->drawTriangleStrip(mVb->getSizeVertexList(), 0);

	mSwapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	mSwapChain->release();
	mVb->release();
	GraphicsEngine::getInstance()->release();
}
