#include "LandingGearApplication.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
LandingGearApplication* LandingGearApplication::m_instance = NULL;

LandingGearApplication * LandingGearApplication::GetInstance(std::string _name)
{
	if (m_instance != NULL) {
		return m_instance;
	}
	else {
		m_instance = new LandingGearApplication(_name);
		return m_instance;
	}
}

void LandingGearApplication::run()
{
	while (m_glwnd->isRuning())
	{
		m_glwnd->render();
	}
}

LandingGearApplication::LandingGearApplication(const std::string & _name)
{
	m_glwnd = new GLWindow();
	m_glwnd->init(SCR_WIDTH, SCR_HEIGHT, _name);
	
	
}

//GLWindow::GLWindow()
//{
//	
//	m_processThread = new std::thread(std::bind(&GLWindow::processUserInteractionEvent,this));
//	m_processThread->detach();
//
//	
//}
 
bool GLWindow::init(int _width, int _height, const std::string name)
{
	Width = _width;
	Height = _height;
	iwndTitle = name;

	m_glctx->init(this);
	m_uictx->init(this);

	//m_gearmodel = new GearModel("./modelsources/Gear/l_door.obj", "./ShaderFiles/model_loading.vs", "./ShaderFiles/model_loading.fs");
	m_gearmodel = new GearModel("./Model.ini");
	return m_isRuning;
}

void GLWindow::render()
{
	
	m_glctx->pre_render();
	m_uictx->pre_render();
	//..
	bool x = 1;
	//ImGui::ShowDemoWindow(&x);
			ImGui::Begin("test");
		
			ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
			ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
			ImGui::End();
			

	m_gearmodel->UseShader();
	m_gearmodel->UpdateMat4();
	////.....
	//m_gearmodel->ModelScale(glm::vec3(0.2f, 0.2f, 0.2f));				//Ä£ÐÍËõ·Å
	//
	m_gearmodel->updatePlaneStatus();
	m_gearmodel->DrawMode();


	m_uictx->post_render();
	m_glctx->post_render();

}

void GLWindow::on_scroll(double delta)
{
	m_gearmodel->GetCamera()->processMouseScroll(delta);
	//std::cout << "delta ";
}

void GLWindow::on_key(int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		
	}
}

void GLWindow::on_resize(int width, int height)
{
	Width = width;
	Height = height;
}

void GLWindow::on_close()
{
	m_isRuning = false;
}

void GLWindow::on_mouse_move(double xpos, double ypos)
{
	//std::cout << "move " << xpos << " " << ypos;;
	if (m_firstmouse)
	{
		m_lastx = static_cast<float>(xpos);
		m_lasty = static_cast<float>(ypos);
		m_firstmouse = false;
	}
	float xoffset = static_cast<float>(xpos) - m_lastx;
	float yoffset = m_lasty - static_cast<float>(ypos);
	m_lastx = static_cast<float>(xpos);
	m_lasty = static_cast<float>(ypos);
	m_gearmodel->GetCamera()->processMouseMovement(xoffset, yoffset);
}

void GLWindow::on_mouse_press(bool _left, bool _right)
{
	button_left_pressed = _left;
	button_right_pressed = _right;
	m_gearmodel->GetCamera()->processMousePress(button_left_pressed, button_right_pressed);
}


