#include "electricvalve.h"
#include <QDebug>

GeneralValve::GeneralValve()
{
  qDebug()<<"valve init...";
  m_odv = new OpenDoorVlave();
  m_cdv = new CloseDoorVlave();
  m_egv = new ExtendGearValve();
  m_rgv = new RetracteGearValve();


  this->m_status = STATUS::OFF;

//  qDebug()<<m_odv->GetStatus();
//  m_odv->open();
//  qDebug()<<m_odv->GetStatus();

}

void GeneralValve::close()
{

}

AbstractValve::AbstractValve()
{

}
