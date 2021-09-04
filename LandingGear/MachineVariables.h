#ifndef MACHINEVARIABLES_H
#define MACHINEVARIABLES_H


enum door_actset{
    op,cl
};

enum gear_actset{
    ex,rt
};

//定义相关消息变量
namespace  envmsgvar{
    extern bool gear_extended;
    extern bool gear_retracted;
   extern  bool gear_extending;
    extern bool gear_retracting;

   extern  bool door_closed;
   extern  bool door_open;
   extern  bool door_opening;
   extern  bool door_closing;

   extern bool pressurizing;
   extern bool depressurizing;
   extern bool circuit_pressurized;
}

namespace  swmsgvar{
   extern door_actset door_act;
   extern gear_actset gear_act;

   extern bool close_EV;
   extern bool open_EV;
   extern bool retract_EV;
   extern bool extend_EV;
   extern bool general_EV;

   extern bool analogical_switch;

   extern bool ana_closing;

}

#endif // MACHINEVARIABLES_H
