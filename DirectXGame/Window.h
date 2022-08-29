#pragma once
#include <Windows.h>

class Window
{
public:
	bool init();
	bool release();
	bool broadcast();
	bool isRun();
	RECT getClientWindowRect();
	void setHWND(HWND hWnd);

	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();
protected:
	HWND mHwnd;
	bool mIsRun;
};
