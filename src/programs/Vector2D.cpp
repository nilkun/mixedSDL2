#include "../headers/Vector2D.h"
#include <cmath>
#include <limits>

void Vector2D::zero()
{
    x = 0.0;
    y = 0.0;
}

bool Vector2D::isZero()const
{
    return (x == 0.0 && y == 0.0);
}

double Vector2D::length()const
{
    // returns the hypoteneuse
    return sqrt(x * x + y * y);
}

double Vector2D::lengthSq()const
{
    return x*x + y*y;
}

void Vector2D::normalize()
{
    double vector_length = this->length();

    if(vector_length > std::numeric_limits<double>::epsilon())
    {
        this->x /= vector_length;
        this->y /= vector_length;
    }
}
double Vector2D::dot(const Vector2D& v2)const
{
    return x*v2.x + y*v2.y;
}
int Vector2D::sign(const Vector2D& v2)const
{
    enum { clockwise = 1, anticlockwise = -1 };
    if(y*v2.x > x*v2.y) return anticlockwise;
    else return clockwise;
}
Vector2D Vector2D::perp()const
{
    return Vector2D(-y, x);
}
void Vector2D::truncate(double max)
{
    if(this->length() > max)
    {
        this -> normalize();

        *this *= max;
    }
}
double Vector2D::distance(const Vector2D &v2)const
{
    double ySeparation = v2.y - y;
    double xSeparation = v2.x - x;

    return sqrt(ySeparation * ySeparation + xSeparation * xSeparation);
}

double Vector2D::distanceSq(const Vector2D &v2)const
{
    double ySeparation = v2.y - y;
    double xSeparation = v2.x - x;

    return ySeparation * ySeparation + xSeparation * xSeparation;
}

Vector2D Vector2D::getReverse()const
{
    return Vector2D(-this->x, -this->y);
}


const Vector2D& Vector2D::operator+=(const Vector2D &rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}
const Vector2D& Vector2D::operator-=(const Vector2D &rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}
const Vector2D& Vector2D::operator*=(const double& rhs)
{
    x *= rhs;
    y *= rhs; 
    return *this;
}
const Vector2D& Vector2D::operator/=(const double& rhs)
{
    x /= rhs;
    y /= rhs;

    return *this;
}
bool Vector2D::operator==(const Vector2D &rhs)const
{
    return (fabs(x-rhs.x) < 1E-12) && fabs(y-rhs.y) < 1E-12;
}
bool Vector2D::operator!=(const Vector2D &rhs)const
{
    return (x != rhs.x) || (y != rhs.y);
}

// inline Vector2D Vector2D::operator*(double rhs)
// {
//   Vector2D result(*this);
//   result *= rhs;
//   return result;
// }
//     inline Vector2D Vector2D::operator*(double rhs, const Vector2D &rhs)
//     {
//   Vector2D result(rhs);
//   result *= lhs;
//   return result;
// inline Vector2D operator*(double rhs);
//     // inline Vector2D operator*(double lhs, const Vector2D &rhs);
//     inline Vector2D operator-(const Vector2D &rhs);
//     inline Vector2D operator+(const Vector2D &rhs);
//     inline Vector2D operator/(double val);
//     }
// inline Vector2D Vector2D::operator-(const Vector2D &rhs)
// {                      
//     Vector2D result(*this);
//     result.x -= rhs.x;
//     result.y -= rhs.y;

//     return result;
// }    
// inline Vector2D Vector2D::operator+(const Vector2D &rhs)
// {                      
//     Vector2D result(*this);
//     result.x += rhs.x;
//     result.y += rhs.y;

//     return result;
// }
// inline Vector2D Vector2D::operator/(double val)
// {
//     Vector2D result(*this);
//     result.x /= val;
//     result.y /= val;

//     return result;
// }


Vector2D Vec2DNormalize(const Vector2D &v)
{
  Vector2D vec = v;

  double vector_length = vec.length();

  if (vector_length > std::numeric_limits<double>::epsilon())
  {
    vec.x /= vector_length;
    vec.y /= vector_length;
  }

  return vec;
}