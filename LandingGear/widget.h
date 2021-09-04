#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include "analogswitch.h"
#include "landinggeardoor.h"
#include "controller.h"
#include "gear.h"

namespace Ui {
  class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

public:
  static Widget* widget;
  explicit Widget(QWidget *parent = nullptr);
  ~Widget();
  void paintEvent(QPaintEvent* event);



  void InitHandShank();
  void InitSystem();

  void UpdateAllEntityStatus();                 //更新所有部件状态
    void accpetclient();
private:
  Ui::Widget *ui;

  LandingGearDoor* m_lgd;                        //起落架门
  Controller* m_ctr;                                      //控制器
  HandShank* m_hs;                                    //手柄
  AnalogSwitch* m_as;                               //模拟开关
  LandingGear* m_ger;                              //起落架

  QTimer *m_timer;               //状态更新频率
  QTcpServer* m_tcpserver;
    QTcpSocket* clientSocket;
};

#endif // WIDGET_H
