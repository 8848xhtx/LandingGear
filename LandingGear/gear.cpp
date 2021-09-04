#include "gear.h"
#include "electricvalve.h"
#include <QtMath>
#include <QtDebug>
#include "MachineVariables.h"

#define PI 3.1415926
#define RAD (PI/180)
using namespace swmsgvar;
using namespace envmsgvar;

void LandingGear::env_gear_retracting()
{
   if(gear_retracted == true || gear_extending == true)
   {
       if(retract_EV == true)
       {
           gear_extended = false;
           gear_retracting = true;
           gear_extending = false;
       }
   }
}

void LandingGear::env_gear_retracted()
{
   if(gear_extended == false)
   {
       if(gear_retracted == false)
       {
           if(retract_EV == true)
           {
               if(gear_retracting == true)
               {
                   gear_retracted = true;
                   gear_retracting = false;
               }
           }
       }
   }
}

void LandingGear::env_gear_extending()
{
   if(gear_retracted == true || gear_retracting == true)
   {
       if(extend_EV == true)
       {
           gear_retracted = false;
           gear_extending = true;
           gear_retracting = false;
       }
   }
}

void LandingGear::env_gear_extended()
{
    if(gear_extended == false && gear_retracted == false)
    {
        if(extend_EV  == true)
        {
            if(gear_extending == true)
            {
                gear_extended = true;
                gear_extending = false;
            }
        }
    }
}

LandingGear::LandingGear(QWidget *parent) : QWidget(parent)
{
  m_status = STATUS::RETRACTED;
  m_rad = 0;
  m_timer = new QTimer(this);
  m_timer->setInterval(20);
  m_connectpos = QPoint(400,400);
  m_tailpos = QPoint(320,400);
  m_length = 80;

  connect(m_timer,&QTimer::timeout,this,&LandingGear::UpdateGear);


  //创建与之对应的指示灯
  m_gl = new GreenLight(QPoint(200,500),GreenLight::OFF);
  m_ol  = new OrangeLight(QPoint(300,500),OrangeLight::OFF);


}

void LandingGear::OpenGear()
{

  if(m_status != STATUS::EXTENDED && m_status != STATUS::EXTENDING)
    {
      qDebug()<<"???>>: "<<m_status;
      m_status = STATUS::EXTENDING;
      m_timer->start();
    }

}

void LandingGear::CloseGear()
{

  if(m_status != STATUS::RETRACTED && m_status != STATUS::RETRACTING)
    {
       m_status = STATUS::RETRACTING;
       m_timer->start();
    }


}

void LandingGear::Stop()
{
  m_status = STATUS::STOP;
  m_timer->stop();

  m_ol->TurnOff();
  m_gl->TurnOff();
}

void LandingGear::UpdateGear()
{
    //qDebug()<<"gear: " <<m_rad;
  if(m_status == STATUS::STOP)return;

  if(m_status == STATUS::EXTENDING && m_egv->GetStatus() == ExtendGearValve::ON)
    {
      if(m_rad >= 90){
          m_status = STATUS::EXTENDED;
          m_timer->stop();

          m_gl->TurnOn();
          m_ol->TurnOff();

        }
      else {
          m_ol->TurnOn();
          m_gl->TurnOff();
          m_tailpos.setX(m_length -  (m_length * cos(m_rad *RAD)) + 320 );
          m_tailpos.setY(  (m_length * sin(m_rad * RAD)) + 400);
          m_rad +=1;

          if(m_rad % 5 == 0)m_connectpos.setX(m_connectpos.x() -1);
        }
     }


  if(m_status == STATUS::RETRACTING && m_egv->GetStatus() == RetracteGearValve::ON)
    {
      if(m_rad <= 0 )
        {
          m_status = STATUS::RETRACTED;
          m_timer->stop();

          m_ol->TurnOff();

           emit closeDoor();

        }
      else {
          m_ol->TurnOn();
          m_gl->TurnOff();
          m_tailpos.setX(m_length -  (m_length * cos(m_rad *RAD)) + 320 );
          m_tailpos.setY(  (m_length * sin(m_rad * RAD)) + 400);
          m_rad -=1;

          if(m_rad % 5 == 0)m_connectpos.setX(m_connectpos.x() +1);

        }
    }
}















