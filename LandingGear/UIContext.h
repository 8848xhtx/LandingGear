#pragma once
#include "RenderContext.h"

class UIContext :public RenderContext {

public:
	void init(IWindow* _wnd) override;

	void pre_render() override;

	void post_render() override;

	void end() override;
};