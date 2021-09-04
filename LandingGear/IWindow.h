#pragma once
#include <string>
class IWindow {
public:
	virtual void* getNativeWindow() = 0;
	virtual void setNativeWindow(void* _wnd) = 0;

	virtual void on_scroll(double _delta) = 0;

	virtual void on_key(int key, int scancode, int action, int mods) = 0;

	virtual void on_resize(int width, int height) = 0;

	virtual void on_close() = 0;

	virtual void on_mouse_move(double _xpos, double _ypos) = 0;

	virtual void on_mouse_press(bool _right, bool _left) = 0;

	int Width;
	int Height;
	std::string iwndTitle;
};