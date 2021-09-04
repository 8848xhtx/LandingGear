#pragma once
#include "../ClassObject/model.hpp"
#include "../ClassObject/shader.hpp"
#include <string>
class IModel {
public:
	IModel(const std::string modelPath,const std::string vs,const std::string fs);
	void UseShader();
	void DrawModel(glm::mat4 _projection,glm::mat4 _view);
	void Scale(glm::vec3 _v);
	void Rotate(float _angle, glm::vec3 _v);
	void Translate(glm::vec3 _v);
private:
	Model* m_model;
	Shader* m_shader;

	glm::mat4 m_modelMat;
	
};