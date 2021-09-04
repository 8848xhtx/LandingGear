#pragma once
#include "../ClassObject/model.hpp"
#include "../ClassObject/shader.hpp"
#include "../ClassObject/camera.hpp"
#include "def.h"
#include "IModel.h"
#include "CommunicationThread.h"
#include <thread>


class GearModel {
public:
	GearModel(const std::string _modepath, const char* vertexPath, const char* fragmentPath);
	GearModel(const std::string _iniPath);
	~GearModel();
	void DrawMode();
	void UseShader();
	void UpdateMat4();
	void SetGearMat4();
	Camera* GetCamera() { return m_camera; }

	void ModelScale(const glm::vec3 _vec3);
	void ModelTranslate(const glm::vec3 _vec3);
	void ModelRotate(const glm::vec3 _vec3, const float _angle);
	void updatePlaneStatus();

	void th_update_angle();
private:
	IModel* m_fuselagemodel;			//ÆðÂä¼ÜÄ£ÐÍ
	IModel* m_nose_gear;
	IModel* m_right_gear;
	IModel* m_left_gear;
	IModel* m_nose_door;
	IModel* m_left_door;
	IModel* m_right_door;

	Shader* m_gearshader;
	Camera* m_camera;

	glm::mat4 m_model;
	glm::mat4 m_nose_gear_mat4;
	glm::mat4 m_right_gear_mat4;
	glm::mat4 m_left_gear_mat4;
	glm::mat4 m_nose_door_mat4;
	glm::mat4 m_left_door_mat4;
	glm::mat4 m_right_door_mat4;



	glm::mat4 m_projection;
	glm::mat4 m_view;

	float m_nose_door_angle = 0;
	float m_right_door_angle = 0;
	float m_left_door_angle = 0;

	float m_right_gear_angle = 0;
	float m_left_gear_angle = 0;
	float m_nose_gear_angle = 0;

	std::thread* m_th;
	CommThread* m_CT;
};