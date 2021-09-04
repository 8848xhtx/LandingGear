#ifndef LANDINGGEARCLOCK_H
#define LANDINGGEARCLOCK_H

#include <QObject>
#include <QTimer>

class GlobalClock : public QObject{
  Q_OBJECT
public:
  GlobalClock();
  ~GlobalClock();
  static GlobalClock* GetClockInstance();
 void StepTime();
private:
  static GlobalClock* m_instance;
  unsigned long long m_gClk;
  QTimer * m_gtimer;

};

class LandingGearClock : public QObject
{
  Q_OBJECT
public:
  explicit LandingGearClock(QObject *parent = nullptr);

signals:

};

#endif // LANDINGGEARCLOCK_H
