#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

class AppWindow: public Window
{
public:
	AppWindow();
	~AppWindow();

	// Window을(를) 통해 상속됨
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* mSwapChain;
	VertexBuffer* mVertexBuffer;
	VertexShader* mVertexShader;
};

