#include "landinggeardoor.h"
#include "electricvalve.h"
#include <QPainter>
#include "widget.h"
#include <QtMath>
#include <QtDebug>
#include "MachineVariables.h"
#define PI 3.1415926
#define RAD (PI/180)
#define OPENRAD 120
#define OPENSPEED 20
using namespace envmsgvar;
using namespace swmsgvar;

LandingGearDoor::LandingGearDoor(QWidget *parent) : QWidget(parent)
{
  m_timer = new QTimer(this);



  m_status = STATUS::CLOSE;
  m_connectPoint = QPoint(400,400);
  m_TailPoint = QPoint(300,400);
  m_length = 100;
  m_rad = 0.0;


  m_timer->setInterval(OPENSPEED);
  connect(m_timer,&QTimer::timeout,this,&LandingGearDoor::UpdateDoor);

}

void LandingGearDoor::env_door_opening()
{
    if(door_closed ==true || door_closing == true)
    {
        if(open_EV == true)
        {
            door_closed = false;
            door_opening = true;
            door_closing = false;
        }
    }
}

void LandingGearDoor::env_door_opened()
{
   if(door_closed == false && door_open == false)
   {
       if(open_EV == true)
       {
           if(door_opening == true)
           {
               door_open = true;
               door_opening = false;
           }
       }
   }
}

void LandingGearDoor::env_door_closing()
{
   if(door_open == true || door_opening == true)
   {
       if(close_EV == true)
       {
           door_open = false;
           door_closing = true;
           door_opening = false;
       }
   }
}

void LandingGearDoor::env_door_closed()
{
  if(door_open == false && door_closed == false)
  {
      if(close_EV == true)
      {
          if(door_closing == true)
          {
              door_closed = true;
              door_closing = false;
          }
      }
  }
}

bool LandingGearDoor::OpenDoor()
{
    if(m_status == STATUS::CLOSE || m_status == STATUS::CLOSING || m_status == STATUS::STOP)
    {
        this-> m_status = STATUS::OPENING;
         qDebug()<<m_status;
         m_timer->start();
    }

}

bool LandingGearDoor::CloseDoor()
{
  qDebug()<<"closedoor";
  if(m_status == STATUS::OPEN || m_status == STATUS::OPENING || m_status == STATUS::STOP)
  {
      m_status = STATUS::CLOSING;
      m_timer->start();
  }


}

void LandingGearDoor::UpdateDoor()
{
if(m_status == STATUS::STOP)return;
//qDebug()<<"door: "<<m_rad;
  //qDebug()<<m_status <<"　...opendoorval: "<< m_odv->GetStatus()<<"  closevsl:　"<< m_cdv->GetStatus();
if(m_status == STATUS::OPENING && m_odv->GetStatus() == OpenDoorVlave::ON)
  {
    //qDebug()<<"ing"<<m_rad << "　"<<m_TailPoint;
    if(m_rad >= OPENRAD)
      {
        m_status = STATUS::OPEN;
        m_timer->stop();

        emit openGear();
        qDebug()<<"emit";

      }
    else{
        m_TailPoint.setX(m_length -  (m_length * cos(m_rad *RAD)) + 300 );
        m_TailPoint.setY(  (m_length * sin(m_rad * RAD)) + 400);
        m_rad +=1;
      }
  }


if(m_status == STATUS::CLOSING && m_cdv->GetStatus() == CloseDoorVlave::ON)
  {
   // qDebug()<<"ing"<<m_rad << "　"<<m_TailPoint;

    if(m_rad <= 0)
      {
        m_status = STATUS::CLOSE;
        m_timer->stop();
      }
    else
      {
        m_TailPoint.setX(m_length -  (m_length * cos(m_rad *RAD)) + 300 );
        m_TailPoint.setY(  (m_length * sin(m_rad * RAD)) + 400);
        m_rad -=1;
      }
  }

}

void LandingGearDoor::ClosingDoor()
{

}

void LandingGearDoor::Stop()
{
  m_status = STATUS::STOP;
  m_timer->stop();

}

//void LandingGearDoor::paintEvent(QPaintEvent* event)
//{
//  QPainter painter(this);

//  painter.setPen(Qt::blue);
//  painter.begin(Widget::widget);


//  switch (m_status) {
//    case STATUS::OPEN: break;
//    case STATUS::CLOSE:break;
//    case STATUS::OPENING:
//      {
//                  m_TailPoint.setX(m_length*cos(m_rad/PI));
//                  m_TailPoint.setY(m_length * sin(m_length / PI));
//      }

//      break;
//    case STATUS::CLOSING:break;


//    }
//painter.drawRect(QRect(100,100,100,100));
//  painter.end();


//}
