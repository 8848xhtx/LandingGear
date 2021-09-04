#ifndef GEAR_H
#define GEAR_H

#include <QWidget>
#include "electricvalve.h"
#include "signallight.h"
#include <QTimer>

//齿轮时间组件
class GearTimeComponent{
  GearTimeComponent();
public:
  //定义相关时间,单位毫秒
  static const int OpenGearTime = 3000;
  static const int CloseGearTime = 3000;
};

class LandingGear : public QWidget
{
    Q_OBJECT
public:
  enum STATUS{
    EXTENDING,          //正在伸出
    RETRACTING,          //正在回收
    EXTENDED,                 //已伸出
    RETRACTED ,          //已回收
    STOP                    //
  };

  //some event-b events
public:
  void env_gear_retracting();
  void env_gear_retracted();
  void env_gear_extending();
  void env_gear_extended();


public:
  explicit LandingGear(QWidget *parent = nullptr);

  QPoint GetTailpos(){return m_tailpos;}
  QPoint GetConpos(){return m_connectpos;}
  int GetStatus(){return m_status;}

  void OpenGear();
  void CloseGear();
  void GetValve(ExtendGearValve* _egv,RetracteGearValve* _rgv){m_egv = _egv;m_rgv = _rgv;}

  void Stop();

  void UpdateGear();

signals:
  void closeDoor();

private:
  QPoint m_connectpos;
  QPoint m_tailpos;
  int m_length;

  QTimer* m_timer;
  int m_status;
  int m_rad;

  ExtendGearValve* m_egv;
  RetracteGearValve* m_rgv;

  GreenLight* m_gl;
  OrangeLight* m_ol;

  GearTimeComponent* m_gearclk;       //定义齿轮时间组件
};

#endif // GEAR_H
