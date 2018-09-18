#ifndef MOVINGENTITY_H_
#define MOVINGENTITY_H_
#include "../engine/headers/GameEntity.h"
#include "Vector2D.h"

class MovingEntity : public GameEntity
{
protected:

    Vector2D m_vVelocity;

    // Normalized vector pointing in the heading direction.
    Vector2D m_vHeading;

    // perpendicular to heading
    Vector2D m_vSide;

    double m_dMass;

    double m_dMaxSpeed;

    double m_dMaxForce;

    double m_dMaxTurnRate;

      //its location in the environment

public:

    Vector2D m_vPos;
    
};

#endif