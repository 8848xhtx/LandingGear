#include "analogswitch.h"
#include "widget.h"
#include <QDebug>
#include <QLabel>

AnalogSwitch::AnalogSwitch()
{
  m_abtn = new QPushButton(Widget::widget);
  m_abtn->resize(50,50);
  m_abtn->move(600,200);
  m_abtn->setStyleSheet("background-color: rgb(225,225,225)");
  m_abtn->show();


  QLabel *lab  = new QLabel("模拟开关");
  lab->move(660,200);
  lab->setParent(Widget::widget);
  lab->show();

  connect(m_abtn,&QPushButton::clicked,this,&AnalogSwitch::updatestatus);
}

void AnalogSwitch::updatestatus()
{
  qDebug()<<"update";
  if(m_status == STATUS::OPEN){
      m_status = STATUS::CLOSE;
      m_abtn->setStyleSheet("background-color: rgb(225, 225, 225)");

    }
  else{
      m_status = STATUS::OPEN;
      m_abtn->setStyleSheet("background-color: rgb(10,220,10)");
    }
}



HandShank::HandShank(Controller* _ctr,AnalogSwitch* _as):m_ctr(_ctr),m_as(_as)
{



  qDebug()<<"///";
  this->setParent(Widget::widget);
  m_upbtn = new QPushButton(Widget::widget);
  m_stopbtn = new QPushButton(Widget::widget);
  m_downbtn = new QPushButton(Widget::widget);

  m_upbtn->move(600,20);
  m_upbtn->show();

  m_stopbtn->move(600,70);
  m_stopbtn->show();

  m_downbtn->move(600,120);
  m_downbtn->show();

  //初始手柄处于中间位置
  m_status = STATUS::STOP;
  m_stopbtn->setStyleSheet("background-color: rgb(123,120,255)");
  m_upbtn->setStyleSheet("background-color: rgb(225, 225, 225)");
  m_downbtn->setStyleSheet("background-color: rgb(225, 225, 225)");


  //绑定信号槽
  connect(m_upbtn,&QPushButton::clicked,this,&HandShank::updateStatus_up);
  connect(m_stopbtn,&QPushButton::clicked,this,&HandShank::updateStatus_stop);
  connect(m_downbtn,&QPushButton::clicked,this,&HandShank::updateStatus_down);


  QLabel *labup  = new QLabel("伸出");
  labup->move(660,20);
  labup->setParent(Widget::widget);
  labup->show();

  QLabel *labstop  = new QLabel("停止");
  labstop->move(660,70);
  labstop->setParent(Widget::widget);
  labstop->show();

  QLabel *labdown  = new QLabel("回收");
  labdown->move(660,120);
  labdown->setParent(Widget::widget);
  labdown->show();


  handle = Handle::DN;

}

void HandShank::updateStatus_up()
{
  qDebug()<<"begin";
  m_status = STATUS::UP;
  m_upbtn->setStyleSheet("background-color: rgb(123,120,255)");
  m_stopbtn->setStyleSheet("background-color: rgb(225, 225, 225)");
  m_downbtn->setStyleSheet("background-color: rgb(225, 225, 225)");

if(m_as->GetStatus() == AnalogSwitch::OPEN)
m_ctr->openLandingGear();

}

void HandShank::updateStatus_stop()
{
  m_status = STATUS::STOP;
  m_stopbtn->setStyleSheet("background-color: rgb(123,120,255)");
  m_upbtn->setStyleSheet("background-color: rgb(225, 225, 225)");
  m_downbtn->setStyleSheet("background-color: rgb(225, 225, 225)");

  if(m_as->GetStatus() == AnalogSwitch::OPEN)
    {
        m_ctr->StopAction();
    }

}

void HandShank::updateStatus_down()
{
  m_status = STATUS::DOWN;
  m_downbtn->setStyleSheet("background-color: rgb(123,120,255)");
  m_stopbtn->setStyleSheet("background-color: rgb(225, 225, 225)");
  m_upbtn->setStyleSheet("background-color: rgb(225, 225, 225)");

if(m_as->GetStatus() == AnalogSwitch::OPEN)
  m_ctr->CloseLandingGear();
// qDebug()<<"close...";
}

void HandShank::env_handle_up()
{
    if(handle == Handle::DN)
    {
        handle = Handle::UP;
    }
}

void HandShank::env_handle_dn()
{
    if(handle == Handle::UP)
    {
        handle = Handle::DN;
    }
}
