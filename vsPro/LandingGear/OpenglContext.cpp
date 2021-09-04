#include "OpenglContext.h"
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto pWindow = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
	pWindow->on_key(key, scancode, action, mods);
}

static void on_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	auto pWindow = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
	pWindow->on_scroll(yoffset);
}

static void on_window_size_callback(GLFWwindow* window, int width, int height)
{
	auto pWindow = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
	pWindow->on_resize(width, height);
}

static void on_window_close_callback(GLFWwindow* window)
{
	IWindow* pWindow = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
	pWindow->on_close();
}

static void on_mouse_move_callback(GLFWwindow* window, double x, double y)
{
	bool button_left_pressed = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
	bool button_right_pressed = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
	IWindow* pWindow = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
	pWindow->on_mouse_move(x, y);
	pWindow->on_mouse_press(button_left_pressed, button_right_pressed);
}
void OpenglContext::init(IWindow * _wnd)
{
	__super::init(_wnd);			//调用父类接口

	//初始化opengl
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* glwnd = glfwCreateWindow(_wnd->Width, _wnd->Height, _wnd->iwndTitle.c_str(), NULL, NULL);
	_wnd->setNativeWindow(glwnd);
	glfwSetWindowUserPointer(glwnd, _wnd);


	glfwSetKeyCallback(glwnd, on_key_callback);
	glfwSetScrollCallback(glwnd, on_scroll_callback);
	glfwSetWindowSizeCallback(glwnd, on_window_size_callback);
	glfwSetWindowCloseCallback(glwnd, on_window_close_callback);
	glfwSetCursorPosCallback(glwnd, on_mouse_move_callback);
	glfwMakeContextCurrent(glwnd);

	if (glwnd == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	//开启深度检测
	glEnable(GL_DEPTH_TEST);
}

void OpenglContext::pre_render()
{
	glViewport(0, 0, mIWindow->Width, mIWindow->Height);
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenglContext::post_render()
{
	glfwSwapBuffers((GLFWwindow*)mIWindow->getNativeWindow());
	glfwPollEvents();
}

void OpenglContext::end()
{
	glfwDestroyWindow((GLFWwindow*)mIWindow->getNativeWindow());
	glfwTerminate();
}
