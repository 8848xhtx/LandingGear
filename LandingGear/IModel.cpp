#include "IModel.h"

IModel::IModel(const std::string modelPath, const std::string vs, const std::string fs)
{
	m_model = new Model(modelPath);
	m_shader = new Shader(vs.c_str(), fs.c_str());
}

void IModel::UseShader()
{
	m_shader->use();
	m_modelMat = glm::mat4(1.0f);
}

void IModel::DrawModel(glm::mat4 _projection, glm::mat4 _view)
{
	m_shader->setMat4("model", m_modelMat);
	m_shader->setMat4("projection", _projection);
	m_shader->setMat4("view", _view);
	m_model->Draw(*m_shader);
}

void IModel::Scale(glm::vec3 _v)
{
	m_modelMat = glm::scale(m_modelMat, _v);
}

void IModel::Rotate(float _angle, glm::vec3 _v)
{
	m_modelMat = glm::rotate(m_modelMat, glm::radians(_angle), _v);
}

void IModel::Translate(glm::vec3 _v)
{
	m_modelMat = glm::translate(m_modelMat, _v);
}
