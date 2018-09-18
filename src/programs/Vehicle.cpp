#include "../headers/Vehicle.h"
#include <limits>
#include <cmath>

bool Vehicle::update(double time_elapsed)
{
    Vector2D steeringForce; // = m_pSteering->Calculate();

    // TESTING

    steeringForce = Seek(); 
    

    if (abs(target.x - m_vPos.x) < 1 && (abs(m_vPos.y - target.y)) < 1)
    {
        m_vVelocity.x = 0;
        m_vVelocity.y = 0;
    }
    else
    {
        // Acceleration = Force / Mass
        Vector2D acceleration = steeringForce / m_dMass;

        // update velocity 
        m_vVelocity += acceleration * time_elapsed;

        m_vVelocity.truncate(m_dMaxSpeed); 
        m_vPos += m_vVelocity * time_elapsed;
        if(m_vVelocity.lengthSq() > 0.000001)
        {
            m_vHeading = Vec2DNormalize(m_vVelocity);
            m_vSide = m_vHeading.perp();
        }
    }


    //update position 

    return true;
}

Vector2D Vehicle::Seek()
{
  Vector2D DesiredVelocity = Vec2DNormalize(target - m_vPos)
                            * m_dMaxSpeed;

  return (DesiredVelocity - m_vVelocity);
}
