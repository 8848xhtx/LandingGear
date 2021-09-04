#ifndef SWSYSTEM_H
#define SWSYSTEM_H

#include <QObject>
#include "LandingGearContext.h"

class SwSystem : public QObject
{
    Q_OBJECT
public:
    explicit SwSystem(QObject *parent = nullptr);
//定义事件

  void treat_hndl_up1();
  void treat_hndl_up2();
  void treat_hndl_up31();
  void treat_hndl_up32();
  void treat_hndl_dn1();
  void treat_hndl_dn2();
  void treat_hndl_dn31();
  void treat_hndl_dn32();

  void treat_door_opening();
  void treat_door_inv_opening();
  void treat_door_open();
  void treat_door_closing();
  void treat_door_inv_closing();
  void tteat_door_closed();

  void treat_gear_retracting();
  void treat_gear_inv_retracting();
  void treat_gear_retracted();
  void treat_gear_extending();
  void treat_gear_inv_extending();
  void treat_gear_extended();


  void treat_start_door_op_when_handle_up();
  void treat_start_door_op_when_handle_dn();
  void treat_start_door_cl_when_handle_up();
  void treat_start_door_cl_when_handle_dn();

  void treat_start_gear_rt_when_handle_up();
  void treat_start_gear_ex_when_handle_dn();


    //纯软件变量，无法被环境观察
private:
    Handle hndl;
    Door door;
    Gear gear;
};

#endif // SWSYSTEM_H
