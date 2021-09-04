#include "signallight.h"
#include "widget.h"
#include <QLabel>

SignalLight::SignalLight()
{

}

GreenLight::GreenLight(QPoint _pos, int _status)
{
  this->move(_pos);
  m_status = _status;
  this->setParent(Widget::widget);
  if(m_status == ON)  this->setStyleSheet("background-color: rgb(0,255,0)");
 else  this->setStyleSheet("background-color: rgb(162, 255, 165)");

  this->show();

  QLabel* lab = new QLabel("指示灯");
  lab->setParent(Widget::widget);
  lab->move(150,500);
  lab->show();
}

void GreenLight::TurnOn()
{
  if(m_status == STATUS::OFF)
    this->setStyleSheet("background-color: rgb(0,255,0)");

  m_status  = STATUS::ON;
}

void GreenLight::TurnOff()
{
  if(m_status == STATUS::ON)
   this->setStyleSheet("background-color: rgb(162, 255, 165)");

  m_status  = STATUS::OFF;

}

OrangeLight::OrangeLight(QPoint _pos, int _status)
{
  this->move(_pos);
  m_status = _status;
  this->setParent(Widget::widget);
  if(m_status == ON)  this->setStyleSheet("background-color: rgb(255, 114, 43)");
 else  this->setStyleSheet("background-color: rgb(255, 231, 156)");

  this->show();
}

void OrangeLight::TurnOn()
{
  if(m_status == STATUS::OFF)
    this->setStyleSheet("background-color:rgb(255, 114, 43)");

  m_status = STATUS::ON;

}

void OrangeLight::TurnOff()
{
  if(m_status == STATUS::ON)
    this->setStyleSheet("background-color: rgb(255, 231, 156)");

  m_status = STATUS::OFF;
}

RedLight::RedLight(QPoint _pos, int _status)
{
  this->move(_pos);
  m_status = _status;
  this->setParent(Widget::widget);
  if(m_status == ON)  this->setStyleSheet("background-color: rgb(255, 0, 0)");
 else  this->setStyleSheet("background-color: rgb(255, 107, 97)");

  this->show();
}

void RedLight::TurnOn()
{
  if(m_status == STATUS::OFF)
    this->setStyleSheet("background-color: rgb(255, 0, 0)");

  m_status = STATUS::ON;
}

void RedLight::TurnOff()
{
  if(m_status == STATUS::ON)
    this->setStyleSheet("background-color: rgb(255, 107, 97)");

  m_status = STATUS::OFF;
}
