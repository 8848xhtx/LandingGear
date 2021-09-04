#ifndef LANDINGGEARDOOR_H
#define LANDINGGEARDOOR_H

#include <QWidget>
#include <QTimer>
#include "electricvalve.h"

//门的时间组件,单位毫秒
class GearDoorTimeComponent{
  GearDoorTimeComponent();
public:
  static const int OpenDoorTime = 3000;
  static const int CloseDoorTime = 3000;

};

class LandingGearDoor : public QWidget
{
  Q_OBJECT
public:
  enum STATUS{
    OPENING,
    CLOSING,//
    OPEN,
    CLOSE,//
    STOP
  };
public:
  explicit LandingGearDoor(QWidget *parent = nullptr);


  //some event-b events
  void env_door_opening();
  void env_door_opened();
  void env_door_closing();
  void env_door_closed();



  bool OpenDoor();
  bool CloseDoor();
  void UpdateDoor();
  void ClosingDoor();
  void Stop();



  void SetStatus(int _type){m_status = _type;}
  int GetStatus(){return m_status;}
  void Setconpos(QPoint _pos){m_connectPoint = QPoint(_pos);}
  void Settailpos(QPoint _pos){m_TailPoint = QPoint(_pos);}
  void SetRad(double _rad){m_rad = _rad;}

  QPoint Getconpos(){return m_connectPoint;}
  QPoint Gettailpos(){return m_TailPoint;}

  void GetValve(OpenDoorVlave* _odv,CloseDoorVlave* _cdv){m_odv = _odv;m_cdv  = _cdv;}


signals:
  void openGear();

private:
  int m_status;                     //表示门的状态
  QPoint m_connectPoint;
  QPoint m_TailPoint;
  int m_length;
  double m_rad;               //旋转角度

  QTimer * m_timer;               //开关门的计时器

  OpenDoorVlave* m_odv;   //相关电动阀
  CloseDoorVlave* m_cdv;

  GearDoorTimeComponent* m_gearclk;   //定义时间组件

};

#endif // LANDINGGEARDOOR_H
