#ifndef SIGNALLIGHT_H
#define SIGNALLIGHT_H
#include <QObject>
#include <QPushButton>
class GreenLight:public QPushButton
{
public:
  enum STATUS
  {
    ON,OFF
  };
public:
  GreenLight(QPoint _pos,int _status);

  void TurnOn();
  void TurnOff();


private:
  int m_status;
};

class OrangeLight:public QPushButton
{
public:
  enum STATUS
  {
    ON,OFF
  };
public:
  OrangeLight(QPoint _pos,int _status);

  void TurnOn();
  void TurnOff();


private:
  int m_status;
};


class RedLight:public QPushButton
{
public:
  enum STATUS
  {
    ON,OFF
  };
public:
  RedLight(QPoint _pos,int _status);

  void TurnOn();
  void TurnOff();


private:
  int m_status;
};




class SignalLight:public QObject
{
public:
  SignalLight();

private:
  QPushButton* m_greenLight;
  QPushButton* m_orangeLight;
  QPushButton* m_redLight;


};

#endif // SIGNALLIGHT_H
