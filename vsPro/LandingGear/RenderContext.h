#pragma once
#include "IWindow.h"

class RenderContext {

public:

	RenderContext() :mIWindow(nullptr) {}

	virtual void init(IWindow* _wnd) {
		mIWindow = _wnd;
	}

	virtual void pre_render() = 0;

	virtual void post_render() = 0;

	virtual void end() = 0;

protected:
	IWindow* mIWindow;
};