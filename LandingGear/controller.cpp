#include "controller.h"

#include <QDebug>


Controller::Controller(LandingGearDoor* _lgd, LandingGear* _gear):m_lgd(_lgd),m_gear(_gear)
{
  m_gv = new GeneralValve();
  m_gear->GetValve(m_gv->Getextendgearval(),m_gv->Getretractegearval());
  m_lgd->GetValve(m_gv->Getopendoorval(),m_gv->Getclosedoorval());



  //相关的信号与槽
  connect(m_lgd,&LandingGearDoor::openGear,this,&Controller::OpenGear);
  connect(m_gear,&LandingGear::closeDoor,this,&Controller::CloseLandingDoor);

  //打开通用电动阀

   OpenGeneralValve();



  //创建异常指示灯

   m_rl    = new RedLight(QPoint(400,500),RedLight::OFF);
}

void Controller::openLandingGear()
{
  if(m_gv->Getopendoorval()->GetStatus() == OpenDoorVlave::OFF && m_gv->GetStatus() == GeneralValve::ON)
  m_gv->Getopendoorval()->open();

 if(m_lgd->GetStatus() == LandingGearDoor::OPEN)
 {
     m_gear->OpenGear();
 }
 else
 {

    m_lgd->OpenDoor();
 }
}

void Controller::CloseLandingDoor()
{
  if(m_gv->Getclosedoorval()->GetStatus() == CloseDoorVlave::OFF && m_gv->GetStatus() == GeneralValve::ON)
  m_gv->Getclosedoorval()->open();
  m_lgd->CloseDoor();
  //qDebug()<<"close..>>.";

  //m_mv->Getretractegearval()->open();
  //m_gear->CloseGear();

}

void Controller::OpenGeneralValve()
{

  if(m_gv->GetStatus() == GeneralValve::OFF)
  m_gv->open();
}

void Controller::OpenGear()
{
  qDebug()<<"??????????????????????";
    if(m_gv->Getextendgearval()->GetStatus() == ExtendGearValve::OFF && m_gv->GetStatus() == GeneralValve::ON)
  m_gv->Getextendgearval()->open();
  m_gear->OpenGear();
}

void Controller::CloseLandingGear()
{
  if(m_gv->Getretractegearval()->GetStatus() == RetracteGearValve::OFF && m_gv->GetStatus() == GeneralValve::ON)
  m_gv->Getretractegearval()->open();

  if(m_gear->GetStatus() != LandingGear::RETRACTED )
    {
        m_gear->CloseGear();
    }
  else CloseLandingDoor();

}

void Controller::StopAction()
{
  if(m_gear->GetStatus() == LandingGear::RETRACTING || m_gear->GetStatus() == LandingGear::EXTENDING)
    {
        m_gear->Stop();
    }
if(m_lgd->GetStatus() == LandingGearDoor::OPENING || m_lgd->GetStatus() == LandingGearDoor::CLOSING)
  {
      m_lgd->Stop();
  }

}
