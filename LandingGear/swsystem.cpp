#include "swsystem.h"
#include "MachineVariables.h"
using namespace swmsgvar;
using namespace envmsgvar;

bool envmsgvar::gear_extended;
bool envmsgvar::gear_retracted;
bool envmsgvar::gear_extending;
bool envmsgvar::gear_retracting;

bool envmsgvar::door_closed;
bool envmsgvar::door_open;
bool envmsgvar::door_opening;
bool envmsgvar::door_closing;

 bool envmsgvar::pressurizing;
 bool envmsgvar::depressurizing;
 bool envmsgvar::circuit_pressurized;


door_actset swmsgvar::door_act;
gear_actset swmsgvar::gear_act;

bool swmsgvar::close_EV;
bool swmsgvar::open_EV;
bool swmsgvar::retract_EV;
bool swmsgvar::extend_EV;
bool swmsgvar::general_EV;
bool swmsgvar::analogical_switch;


SwSystem::SwSystem(QObject *parent) : QObject(parent)
{
    hndl = Handle::DN;
    door = Door::CL;
    gear = Gear::EX;

    envmsgvar::door_closed = true;
    envmsgvar::door_open = false;
    envmsgvar::gear_extended = true;
    envmsgvar::gear_retracted = false;
    envmsgvar::door_opening = false;
    envmsgvar::door_closing = false;
    envmsgvar::gear_extending = false;
    envmsgvar::gear_retracting = false;

    envmsgvar::pressurizing = false;
    envmsgvar::depressurizing = false;
    envmsgvar::circuit_pressurized = false;

   // swmsgvar::door_act = door_actset::cl;
    //swmsgvar::gear_act = gear_actset::ex;

      swmsgvar::close_EV = false;
      swmsgvar::open_EV = false;
      swmsgvar::retract_EV = false;
      swmsgvar::extend_EV = false;
      swmsgvar::general_EV = false;

}

void SwSystem::treat_hndl_up1()
{
    if(hndl == Handle::DN)
    {
        if((gear_actset)gear == swmsgvar::gear_act)
        {
            if((door_actset)door == swmsgvar::door_act)
            {
               // if(handle == up)
                hndl = Handle::UP;
            }
        }
    }
}

void SwSystem::treat_hndl_up2()
{
    if(hndl == Handle::DN)
    {
        //if(handle == up)
        if(gear != Gear::EX)
        {
            if(gear_act == gear_actset::ex)
            {
                hndl = Handle::UP;
                gear_act = gear_actset::rt;
            }
        }
    }
}

void SwSystem::treat_hndl_up31()
{
    if(hndl == Handle::UP)
    {
        //if(handle == up)
        if(door_act == door_actset::op)
        {
            if(door != Door::OP)
            {
                hndl = Handle::UP;
                door_act = door_actset::cl;
            }
        }
    }
}

void SwSystem::treat_hndl_up32()
{
    if(hndl == Handle::DN)
    {
        //if(handle == up)
        if(door_act == door_actset::cl)
        {
            if(door != Door::CL)
            {
                hndl = Handle::UP;
                door_act = door_actset::op;
            }
        }
    }
}

void SwSystem::treat_hndl_dn1()
{
    if(hndl == Handle::UP)
    {
        if((gear_actset)gear == gear_act)
        {
            if((door_actset)door == door_act)
            {
               // if(handle == up)
                hndl = Handle::DN;
            }
        }
    }
}

void SwSystem::treat_hndl_dn2()
{
    if(hndl == Handle::UP)
    {
        //if(handle == up)
        if(gear != Gear::RT)
        {
            if(gear_act == gear_actset::rt)
            {
                hndl = Handle::DN;
                gear_act = gear_actset::ex;
            }
        }
    }
}

void SwSystem::treat_hndl_dn31()
{
    if(hndl == Handle::UP)
    {
        //if(handle == dn)
        if(door_act == door_actset::op)
        {
            if(door != Door::OP)
            {
                hndl = Handle::DN;
                door_act = door_actset::cl;
            }
        }
    }
}

void SwSystem::treat_hndl_dn32()
{
    if(hndl == Handle::UP)
    {
        //if(handle == dn)
        if(door_act == door_actset::cl)
        {
            if(door != Door::CL)
            {
                hndl = Handle::DN;
                door_act = door_actset::op;
            }
        }
    }
}

void SwSystem::treat_door_opening()
{
    if(door == Door::CL)
    {
        if(open_EV == true)
        {
            if(door_closed == false)
            {
                door = Door::CL2OP;
            }
        }
    }
}

void SwSystem::treat_door_inv_opening()
{
    if(door == Door::OP2CL)
    {
        if(open_EV == true)
        {
            if(door_closed == false)
            {
                door = Door::CL2OP;
            }
        }
    }
}

void SwSystem::treat_door_open()
{
    if(door == Door::CL2OP)
    {
        if(open_EV == true)
        {
            if(door_open == true)
            {
                door = Door::OP;
            }
        }
    }
}

void SwSystem::treat_door_closing()
{
    if(door == Door::OP)
    {
        if(close_EV == true)
        {
            if(door_open == false)
            {
                door = Door::OP2CL;
            }
        }
    }
}

void SwSystem::treat_door_inv_closing()
{
    if(close_EV == true)
    {
        if(door_open == false)
        {
            if(door == Door::CL2OP)
            {
                door = Door::OP2CL;
            }
        }
    }
}

void SwSystem::tteat_door_closed()
{
    if(door == Door::OP2CL)
    {
        if(close_EV == true)
        {
            if(door_closed == true)
            {
                door = Door::CL;
            }
        }
    }
}

void SwSystem::treat_gear_retracting()
{
    if(gear == Gear::EX)
    {
        if(retract_EV == true)
        {
            if(gear_extended == false)
            {
                gear = Gear::EX2RT;
            }
        }
    }
}

void SwSystem::treat_gear_inv_retracting()
{
    if(gear == Gear::RT2EX)
    {
        if(retract_EV == true)
        {
            if(gear_extended == false)
            {
                gear = Gear::EX2RT;
            }
        }
    }
}

void SwSystem::treat_gear_retracted()
{
    if(gear == Gear::EX2RT)
    {
        if(retract_EV == true)
        {
            if(gear_retracted == true)
            {
                gear = Gear::RT;
                retract_EV = false;
            }
        }
    }
}

void SwSystem::treat_gear_extending()
{
    if(gear == Gear::RT)
    {
        if(extend_EV == true)
        {
            if(gear_retracted == false)
            {
                gear = Gear::RT2EX;
            }
        }
    }
}

void SwSystem::treat_gear_inv_extending()
{
    if(gear == Gear::EX2RT)
    {
        if(extend_EV == true)
        {
            if(gear_retracted == false)
            {
                gear = Gear::RT2EX;
            }
        }
    }
}

void SwSystem::treat_gear_extended()
{
    if(gear == Gear::RT2EX)
    {
        if(extend_EV == true)
        {
            if(gear_extended == true)
            {
                gear = Gear::EX;
                extend_EV = false;
            }
        }
    }
}

void SwSystem::treat_start_door_op_when_handle_up()
{
    if(hndl == Handle::UP)
    {
        if(door ==Door::CL && open_EV == false && close_EV == true)
        {
            if(gear == Gear::EX && retract_EV == true && extend_EV == true)
            {
                //if(hndl == hanlde)
                if(door_closed == true)
                {
                    open_EV = true;
                }

            }
        }
    }
}

void SwSystem::treat_start_door_op_when_handle_dn()
{
    if(hndl == Handle::DN)
    {
        if(door == Door::CL && open_EV == false && close_EV == true)
        {
            if(gear == Gear::RT && retract_EV == true && extend_EV == true)
            {
                //if(hndl == handle
                if(door_closed == true)
                {
                    open_EV = true;
                }

            }
        }
    }
}

void SwSystem::treat_start_door_cl_when_handle_up()
{
    if(hndl == Handle::UP)
    {
        if(door == Door::OP && open_EV == true && close_EV == false)
        {
            if(gear == Gear::RT )
            {
                if(gear_retracted == true)
                {
                    //ifhndl == handle
                   close_EV = true;
                   retract_EV = false;
                   extend_EV = false;
                   open_EV = false;
                }
            }
        }
    }
}

void SwSystem::treat_start_door_cl_when_handle_dn()
{
    if(hndl == Handle::DN)
    {
        if(door == Door::OP && open_EV == true && close_EV == false)
        {
            if(gear == Gear::EX )
            {
                if(gear_extended == true)
                {
                    //if hndl == handle
                    close_EV = true;
                    extend_EV = false;
                    retract_EV = false;
                    open_EV = false;
                }
            }
        }
    }
}

void SwSystem::treat_start_gear_rt_when_handle_up()
{
    if(hndl == Handle::UP)
    {
        if(gear == Gear::EX && extend_EV == false && retract_EV == false)
        {
            if(door == Door::OP &&close_EV == false && open_EV == false)
            {
                if(door_open == true)
                {
                    // if hndl == handle
                   if(gear_extended == true)
                   {
                       retract_EV = true;
                   }
                }
            }
        }
    }
}

void SwSystem::treat_start_gear_ex_when_handle_dn()
{
    //if hndl == handle
    if(hndl == Handle::DN && gear == Gear::RT)
    {
        if(open_EV == true && close_EV == false)
        {
            if(extend_EV == false && retract_EV == false)
            {
                if(door == Door::OP)
                {
                    if(door_open == true && gear_retracted == true)
                    {
                        extend_EV = true;
                    }
                }
            }
        }
    }
}
