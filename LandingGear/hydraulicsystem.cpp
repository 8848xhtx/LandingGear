#include "hydraulicsystem.h"
#include "MachineVariables.h"
using namespace envmsgvar;
using namespace swmsgvar;

HydraulicSystem::HydraulicSystem(QObject *parent) : QObject(parent)
{

}

void HydraulicSystem::env_general_pressurizing()
{
    if(m_gv->GetStatus() == GeneralValve::ON)
    {
        if(m_status != STATUS::PRESSURIZED)
        {
            if(m_status != STATUS::PRESSURIZING)
            {
                m_status = STATUS::PRESSURIZING;
            }
        }
    }



    if(general_EV == true)
    {
        if(circuit_pressurized == false || depressurizing == true)
        {
            if(analogical_switch == true)
            {
                if(pressurizing == false)
                {
                    pressurizing = true;
                    depressurizing = false;
                }
            }
        }
    }

}

void HydraulicSystem::env_general_pressurized()
{
    if(m_gv->GetStatus() == GeneralValve::ON)
    {
        if(m_status != STATUS::PRESSURIZED)
        {
            if(m_status == STATUS::PRESSURIZING)
            {
                m_status = STATUS::PRESSURIZED;
            }
        }
    }



    if(general_EV == true)
    {
        if(circuit_pressurized == false)
        {
            if(pressurizing == true)
            {
                if(analogical_switch == true)
                {
                    circuit_pressurized = true;
                    pressurizing = false;
                }
            }
        }
    }
}

void HydraulicSystem::env_general_depressurizing()
{
    if(general_EV == false)
    {
        if(circuit_pressurized == true)
        {
            if(open_EV == false && close_EV == false)
            {
                if(retract_EV == false && extend_EV == false)
                {
                    //if door == cl
                    if(door_closed == true)
                    {
                        if(depressurizing == false)
                        {
                            depressurizing =true;
                            pressurizing = false;
                            circuit_pressurized = false;
                        }
                    }
                }
            }
        }
    }
}

void HydraulicSystem::env_general_depressurized()
{
    if(general_EV == false)
    {
        if(open_EV == false &&close_EV == false)
        {
            if(retract_EV == false && extend_EV == false)
            {
                //if door == cl
                if(depressurizing == true)
                {
                    depressurizing = false;
                }
            }
        }
    }
}
