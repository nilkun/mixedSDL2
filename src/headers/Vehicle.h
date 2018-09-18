#ifndef VEHICLE_H_
#define VEHICLE_H_
#include "MovingEntity.h"

class Vehicle : public MovingEntity
{
    private:
    //GameWorld* m_pWorld;
    //SteeringBehaviours* m_pSteering;

public:
    bool update(double time_elapsed);
    Vector2D CalculateSum();
    Vector2D Seek();
    Vector2D target;
    Vehicle()
    {
        m_dMass = 0.03;
        m_dMaxSpeed=0.09;
        m_dMaxForce=0.6;
        m_dMaxTurnRate=0.03;
     }
};

#endif