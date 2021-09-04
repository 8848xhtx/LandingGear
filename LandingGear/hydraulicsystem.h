#ifndef HYDRAULICSYSTEM_H
#define HYDRAULICSYSTEM_H

#include <QObject>
#include "electricvalve.h"

class HydraulicSystem : public QObject
{
    Q_OBJECT
public:
    explicit HydraulicSystem(QObject *parent = nullptr);

public:
    enum STATUS{
        PRESSURIZING,           //正在增压
        PRESSURIZED,            //
        DEPRESSURIZING,     //正在减压
        DEPRESSURIZED
    };
    //some event-b events
public:
    void env_general_pressurizing();
    void env_general_pressurized();
    void env_general_depressurizing();
    void env_general_depressurized();


private:
    int m_status;
    GeneralValve* m_gv;
};

#endif // HYDRAULICSYSTEM_H
