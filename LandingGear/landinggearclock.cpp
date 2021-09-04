#include "landinggearclock.h"
#include <QtDebug>

GlobalClock* GlobalClock::m_instance = nullptr;

LandingGearClock::LandingGearClock(QObject *parent) : QObject(parent)
{

}

GlobalClock::~GlobalClock()
{

}
GlobalClock::GlobalClock()
{
  m_gClk = 0;
  m_gtimer = new QTimer(this);
  m_gtimer->setTimerType(Qt::PreciseTimer);             //设置计时器精度
  connect(m_gtimer,&QTimer::timeout,this,&GlobalClock::StepTime);
  m_gtimer->start(1);
}

GlobalClock *GlobalClock::GetClockInstance()
{
  if(m_instance == nullptr)
    {
      return m_instance = new GlobalClock;
    }
  else
    {
      return m_instance;
    }
}

void GlobalClock::StepTime()
{
  m_gClk++;
  //qDebug()<<m_gClk;
}
