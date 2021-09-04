#include "GearModel.h"
#include "GearStatus.h"
#include <Windows.h>
#define ANGLE_DELTA 5.0f

#define ANGLE_DOOR_DELTA 2.5f
#define ANGLE_GEAR_DELTA 3.5f
GearModel::GearModel(const std::string _modelpath, const char* vertexPath, const char* fragmentPath)
{
	//m_fuselagemodel = new Model(_modelpath.c_str());
	//m_gearshader = new Shader(vertexPath, fragmentPath);
	m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}
GearModel::GearModel(const std::string _iniPath)
{
	m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	char str[64];
	char vs[64];
	char fs[64];
	GetPrivateProfileString("PlaneModel", "Model", "", str, 64, _iniPath.c_str());
	GetPrivateProfileString("PlaneModel", "VS", "", vs, 64, _iniPath.c_str());
	GetPrivateProfileString("PlaneModel", "FS", "", fs, 64, _iniPath.c_str());

	std::cout << "model " << str << endl;
	m_fuselagemodel = new IModel(str,vs,fs);
	



	GetPrivateProfileString("NoseGearModel", "Model", "", str, 64, _iniPath.c_str());
	GetPrivateProfileString("NoseGearModel", "VS", "", vs, 64, _iniPath.c_str());
	GetPrivateProfileString("NoseGearModel", "FS", "", fs, 64, _iniPath.c_str());
	std::cout << "model " << str << endl;
	m_nose_gear = new IModel(str, vs, fs);

	GetPrivateProfileString("RightGearModel", "Model", "", str, 64, _iniPath.c_str());
	GetPrivateProfileString("RightGearModel", "VS", "", vs, 64, _iniPath.c_str());
	GetPrivateProfileString("RightGearModel", "FS", "", fs, 64, _iniPath.c_str());
	std::cout << "model " << str << endl;
	m_right_gear = new IModel(str, vs, fs);

	GetPrivateProfileString("LeftGearModel", "Model", "", str, 64, _iniPath.c_str());
	GetPrivateProfileString("LeftGearModel", "VS", "", vs, 64, _iniPath.c_str());
	GetPrivateProfileString("LeftGearModel", "FS", "", fs, 64, _iniPath.c_str());
	std::cout << "model " << str << endl;
	m_left_gear = new IModel(str, vs, fs);


	GetPrivateProfileString("NoseDoorModel", "Model", "", str, 64, _iniPath.c_str());
	GetPrivateProfileString("NoseDoorModel", "VS", "", vs, 64, _iniPath.c_str());
	GetPrivateProfileString("NoseDoorModel", "FS", "", fs, 64, _iniPath.c_str());
	std::cout << "model " << str << endl;
	m_nose_door = new IModel(str, vs, fs);

	GetPrivateProfileString("LeftDoorModel", "Model", "", str, 64, _iniPath.c_str());
	GetPrivateProfileString("LeftDoorModel", "VS", "", vs, 64, _iniPath.c_str());
	GetPrivateProfileString("LeftDoorModel", "FS", "", fs, 64, _iniPath.c_str());
	std::cout << "model " << str << endl;
	m_left_door = new IModel(str, vs, fs);

	GetPrivateProfileString("RightDoorModel", "Model", "", str, 64, _iniPath.c_str());
	GetPrivateProfileString("RightDoorModel", "VS", "", vs, 64, _iniPath.c_str());
	GetPrivateProfileString("RightDoorModel", "FS", "", fs, 64, _iniPath.c_str());
	std::cout << "model " << str << endl;
	m_right_door = new IModel(str, vs, fs);


	m_CT = new CommThread("127.0.0.1", 10086);
	m_th = new std::thread(std::bind(&GearModel::th_update_angle, this));
	m_th->detach();
}
GearModel::~GearModel()
{
	
	delete m_gearshader;
	delete m_camera;
}

void GearModel::DrawMode()
{
	//SetGearMat4();
	//m_gearmodel->Draw(*m_gearshader);

	m_fuselagemodel->DrawModel(m_projection,m_view);
	m_nose_gear->DrawModel(m_projection, m_view);
	m_left_gear->DrawModel(m_projection, m_view);
	m_right_gear->DrawModel(m_projection, m_view);

	m_nose_door->DrawModel(m_projection, m_view);
	m_left_door->DrawModel(m_projection, m_view);
	m_right_door->DrawModel(m_projection, m_view);

}

void GearModel::UseShader()
{
	//m_gearshader->use();

	m_fuselagemodel->UseShader();
	m_nose_gear->UseShader();
	m_left_gear->UseShader();
	m_right_gear->UseShader();

	m_nose_door->UseShader();
	m_left_door->UseShader();
	m_right_door->UseShader();
}

void GearModel::UpdateMat4()
{
	m_projection = glm::perspective(glm::radians(m_camera->mZoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,0.1f,100.0f);
	m_view = m_camera->getViewMatrix();

	/*m_model = glm::mat4(1.0f);
	m_nose_gear_mat4 = glm::mat4(1.0f);
	m_right_gear_mat4 = glm::mat4(1.0f);
	m_left_gear_mat4 = glm::mat4(1.0f);
	m_nose_door_mat4 = glm::mat4(1.0f);
	m_right_door_mat4 = glm::mat4(1.0f);
	m_left_door_mat4 = glm::mat4(1.0f);*/


}

void GearModel::SetGearMat4()
{
	/*m_gearshader->setMat4("model", m_model);
	m_gearshader->setMat4("model", m_nose_gear_mat4);
	m_gearshader->setMat4("model", m_right_gear_mat4);
	m_gearshader->setMat4("model", m_left_gear_mat4);
	m_gearshader->setMat4("model", m_nose_door_mat4);
	m_gearshader->setMat4("model", m_right_door_mat4);
	m_gearshader->setMat4("model", m_left_door_mat4);*/


	/*m_gearshader->setMat4("projection", m_projection);
	m_gearshader->setMat4("view", m_view);*/
}

void GearModel::ModelTranslate(const glm::vec3 _vec3)
{
	m_model = glm::translate(m_model, _vec3);
}

void GearModel::ModelRotate(const glm::vec3 _vec3,const float _angle)
{
	m_model = glm::rotate(m_model,_angle, _vec3);
}

void GearModel::updatePlaneStatus()
{
	/*m_nose_door_mat4 = glm::rotate(m_nose_door_mat4, m_nose_door_angle, glm::vec3(0, 0, 1));

	m_right_door_mat4 = glm::rotate(m_right_door_mat4, m_right_door_angle, glm::vec3(0, 0, 1));

	m_left_door_mat4 = glm::rotate(m_left_door_mat4, m_left_door_angle, glm::vec3(0, 0, 1));

	m_nose_gear_mat4 = glm::rotate(m_nose_gear_mat4, m_nose_gear_angle, glm::vec3(0, 0, 1));

	m_right_gear_mat4 = glm::rotate(m_right_gear_mat4, m_right_gear_angle, glm::vec3(0, 0, 1));

	m_left_gear_mat4 = glm::rotate(m_left_gear_mat4, m_left_gear_angle, glm::vec3(0, 0, 1));*/

	//m_nose_gear_mat4 = glm::rotate(m_nose_gear_mat4, m_nose_gear_angle, glm::vec3(1, 0, 0));
	//m_model = glm::rotate(m_model, m_nose_door_angle, glm::vec3(1.0f, 1.0f, 1.0f));



	//m_model = glm::translate(m_model, glm::vec3(m_nose_door_angle, 0.0f, 0.0f));
	//m_nose_gear_mat4 = glm::translate(m_nose_gear_mat4, glm::vec3(m_nose_door_angle , 0.0f, 0.0f));
	//m_right_gear_mat4 = glm::translate(m_right_gear_mat4, glm::vec3(m_nose_door_angle, 0.0f, 0.0f));
	//m_left_gear_mat4 = glm::translate(m_left_gear_mat4, glm::vec3(m_nose_door_angle, 0.0f, 0.0f));


	//m_nose_door_mat4 = glm::translate(m_nose_door_mat4, glm::vec3(m_nose_door_angle , 0.0f, 0.0f));

	//m_right_door_mat4 = glm::translate(m_right_door_mat4, glm::vec3(m_nose_door_angle , 0.0f, 0.0f));

	//m_left_door_mat4 = glm::translate(m_left_door_mat4, glm::vec3(m_nose_door_angle , 0.0f, 0.0f));
	m_fuselagemodel->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
	m_nose_gear->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
	m_left_gear->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
	m_right_gear->Scale(glm::vec3(0.2f, 0.2f, 0.2f));

	m_nose_door->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
	m_left_door->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
	m_right_door->Scale(glm::vec3(0.2f, 0.2f, 0.2f));

	//m_fuselagemodel->Rotate(m_nose_gear_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	//
	m_nose_gear->Translate(glm::vec3(0.0, 0.0, 4.5));
	m_nose_gear->Rotate(m_nose_gear_angle,glm::vec3(1.0f, 0.0f, 0.0f));
	
	m_left_gear->Translate(glm::vec3(1.2f, -0.5f, -1.5f));
	m_left_gear->Rotate(m_left_gear_angle, glm::vec3(1.0f, 0.0f, 0.0f));


	m_right_gear->Translate(glm::vec3(-1.2f,-0.5f,-1.5f));
	m_right_gear->Rotate(m_right_gear_angle, glm::vec3(1.0f, 0.0f, 0.0f));

	m_nose_door->Translate(glm::vec3(-0.2f, -0.9f, 5.0f));
	m_nose_door->Rotate(m_nose_door_angle, glm::vec3(0.0f, 0.0f, 1.0f));

	m_left_door->Translate(glm::vec3(1.5f, -0.5f, 0.0f));
	m_left_door->Rotate(m_left_door_angle, glm::vec3(0.0f, 0.0f, 1.0f));
	
	m_right_door->Translate(glm::vec3(-1.7f, -0.3f, 0.0f));
	m_right_door->Rotate(m_right_door_angle, glm::vec3(0.0f, 0.0f, -1.0f));

	std::cout << " " << m_nose_door_angle << " " << m_nose_gear_angle << std::endl;
}

void GearModel::th_update_angle()
{
	PlaneStatus status = { NULL };
	while (true)
	{
		m_CT->getStatus(status);
		//std::cout << "door " << status.doorSta << " gear " << status.gearSta << std::endl;
		switch (status.doorSta)
		{
		case STATUS_DOOR_OPENING:
			m_nose_door_angle-=ANGLE_DOOR_DELTA;
			m_right_door_angle+= ANGLE_DOOR_DELTA;
			m_left_door_angle+= ANGLE_DOOR_DELTA;
			break;
		case STATUS_DOOR_CLOSING:
			m_nose_door_angle+= ANGLE_DOOR_DELTA;
			m_right_door_angle-= ANGLE_DOOR_DELTA;
			m_left_door_angle-= ANGLE_DOOR_DELTA;
			break;
		}

		switch (status.gearSta)
		{
		case STATUS_GEAR_EXTENDING:
			m_nose_gear_angle-= ANGLE_GEAR_DELTA;
			m_right_gear_angle-= ANGLE_GEAR_DELTA;
			m_left_gear_angle-= ANGLE_GEAR_DELTA;
			break;
		case STATUS_GEAR_RETRACTING:
			m_nose_gear_angle+= ANGLE_GEAR_DELTA;
			m_right_gear_angle+= ANGLE_GEAR_DELTA;
			m_left_gear_angle+= ANGLE_GEAR_DELTA;
			break;
		}
	}
}

void GearModel::ModelScale(const glm::vec3 _vec3)
{
	m_model = glm::scale(m_model,_vec3);
	m_nose_door_mat4 = glm::scale(m_nose_door_mat4, _vec3);
	m_right_door_mat4 = glm::scale(m_right_door_mat4, _vec3);
	m_left_door_mat4 = glm::scale(m_left_door_mat4, _vec3);
	m_nose_gear_mat4 = glm::scale(m_nose_gear_mat4, _vec3);
	m_right_gear_mat4 = glm::scale(m_right_gear_mat4, _vec3);
	m_left_gear_mat4 = glm::scale(m_left_gear_mat4, _vec3);
}
