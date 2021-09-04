#pragma once
#include <string>
#include "glinclude.h"
#include <iostream>
#include <thread>
#include "GearModel.h"
#include "def.h"
#include "OpenglContext.h"
#include "UIContext.h"


class GLWindow;
class LandingGearApplication {
public:
	
	static LandingGearApplication* GetInstance(std::string _name);
	void run();
private:
	static LandingGearApplication* m_instance;
	LandingGearApplication(const std::string& _name);
	GLWindow* m_glwnd;
	//垃圾类
	class CGarbo {
	public:
		~CGarbo()
		{
			if (LandingGearApplication::m_instance) { delete LandingGearApplication::m_instance; }
		}
	};
	static CGarbo m_garbo;
};

class GLWindow : public IWindow{
public:
	GLWindow() :m_isRuning(true) {
		m_glctx = new OpenglContext();
		m_uictx = new UIContext();
	}
	~GLWindow()
	{

	}
	bool isRuning() { return m_isRuning; }
	bool init(int _width, int _height, const std::string name);
	void setNativeWindow(void* _wnd) { m_window = (GLFWwindow*)_wnd; }
	void* getNativeWindow() { return m_window; }
	void render();
	void on_scroll(double delta) override;

	void on_key(int key, int scancode, int action, int mods) override;

	void on_resize(int width, int height) override;

	void on_close() override;

	void on_mouse_move(double _x, double _y)override;

	void on_mouse_press(bool _right, bool _left)override;
	
	void test() { std::cout << "button\n"; }

private:
	GLFWwindow* m_window;
	//opengl 上下文
	OpenglContext* m_glctx;
	//imgui 上下文
	UIContext* m_uictx;

	bool m_isRuning;

	GearModel* m_gearmodel;
	std::thread* m_processThread;		//用户交互线程

	double m_xpos, m_ypos;						//鼠标位置
	double m_lastx, m_lasty;
	bool m_firstmouse = true;
	bool button_left_pressed, button_right_pressed;
};