#ifndef ANALOGSWITCH_H
#define ANALOGSWITCH_H
#include <QPushButton>
#include  "controller.h"
#include "LandingGearContext.h"

//模拟开关，当模拟开关闭合，控制器才可以发送指令给通用电动阀
class AnalogSwitch:public QObject
{
public:
  enum STATUS{
    OPEN,
    CLOSE
  };
public:
  AnalogSwitch();
  void updatestatus();
  int GetStatus(){return m_status;}
  //void mousePressEvent(QMouseEvent *event);

  QPushButton* m_abtn;
private:
  int m_status;
};


class HandShank:public QObject
{
public:
  enum STATUS{
    UP,
    STOP,
    DOWN
  };

public:
  HandShank(Controller* _ctr,AnalogSwitch* _as);
  int GetStatus(){return m_status;}

  //与鼠标点击相关的槽函数
  void updateStatus_up();
  void updateStatus_stop();
  void updateStatus_down();

  //定义相关事件
  void env_handle_up();
  void env_handle_dn();

private:

  Handle handle;                    //chun 手柄环境var
  QPushButton* m_upbtn;
  QPushButton* m_stopbtn;
  QPushButton* m_downbtn;

  int m_status;


  Controller* m_ctr;
  AnalogSwitch* m_as;

};




#endif // ANALOGSWITCH_H
