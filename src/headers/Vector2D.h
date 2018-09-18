#ifndef VECTOR2D_H_
#define VECTOR2D_H_

struct Vector2D 
{
    double x;
    double y;

    Vector2D():x(0.0), y(0.0){}
    Vector2D(double a, double b):x(a), y(b){}

    void zero();

    bool isZero()const;

    double length()const;

    double lengthSq()const;

    void normalize();

    double dot(const Vector2D& v2)const;

    int sign(const Vector2D& v2)const;

    Vector2D perp()const;

    void truncate(double max);

    double distance(const Vector2D &v2)const;
    double distanceSq(const Vector2D &v2)const;

    Vector2D getReverse()const;

    const Vector2D& operator+=(const Vector2D &rhs);
    const Vector2D& operator-=(const Vector2D &rhs);
    const Vector2D& operator*=(const double& rhs);
    const Vector2D& operator/=(const double& rhs);
    bool operator==(const Vector2D &rhs)const;
    bool operator!=(const Vector2D &rhs)const;

    Vector2D operator*(double rhs)
    {  
        Vector2D result(*this);
        result *= rhs;
        return result;
    }
    // Vector2D operator*(double lhs, const Vector2D &rhs);
    Vector2D operator-(const Vector2D &rhs)
    {                      
        Vector2D result(*this);
        result.x -= rhs.x;
        result.y -= rhs.y;

        return result;
    }   
    Vector2D operator+(const Vector2D &rhs)
    {                      
        Vector2D result(*this);
        result.x += rhs.x;
        result.y += rhs.y;

        return result;
    }
    Vector2D operator/(double val)
    {
        Vector2D result(*this);
        result.x /= val;
        result.y /= val;

        return result;
}

};

Vector2D Vec2DNormalize(const Vector2D &v);

#endif