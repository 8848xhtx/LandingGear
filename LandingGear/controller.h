#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "landinggeardoor.h"
#include "gear.h"
#include "electricvalve.h"
#include "signallight.h"
#include "landinggearclock.h"


class Controller:public QObject
{
public:
  Controller(LandingGearDoor* _lgd,LandingGear* _gear);


  //时间驱动指令
  bool TimeDrive_openLandingGear();
  bool TimeDrive_closeLandingGear();


  //指令信号
  void openLandingGear();
  void CloseLandingDoor();
  void OpenGeneralValve();

  void OpenGear();
  void CloseLandingGear();

  void StopAction();

  void GetAllEntityStatus();                         //获取所有部件状态

private:

  LandingGearDoor * m_lgd;
  LandingGear* m_gear;
  GeneralValve* m_gv;
  RedLight* m_rl;                                   //系统异常指示灯


  LandingGearClock* m_globalCLK;    //定义全局时钟
};

#endif // CONTROLLER_H
