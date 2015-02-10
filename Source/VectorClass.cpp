#include "GlobalHeaders.hpp"
#include "VectorClass.hpp"

using namespace VectorClass;

///////////////////////////////////////////////////////////////
//
//VectorClass//
    //v2d//
        //Vector//

//Operators//
v2d::Vector v2d::Vector::operator * (double mult)
{
    return Vector(this->m_x * mult, this->m_y * mult);
}

v2d::Vector v2d::Vector::operator / (double div)
{
    return Vector(this->m_x / div, this->m_y / div);
}

v2d::Vector v2d::Vector::operator + (v2d::Vector v)
{
    return Vector(this->m_x + v.GetX(), this->m_y + v.GetY());
}

v2d::Vector v2d::Vector::operator - (v2d::Vector v)
{
    return Vector(this->m_x - v.GetX(), this->m_y - v.GetY());
}

v2d::Vector v2d::Vector::operator - ()
{
    return Vector(this->m_x * -1, this->m_y * -1);
}

//Functions//
double v2d::Vector::Dot(v2d::Vector v)
{
    return (
        this->m_x * v.GetX() +
        this->m_y * v.GetY()
        );
}

double v2d::Vector::GetLength()
{
    double len = (pow(m_x, 2) + pow(m_y, 2));
    len = sqrt(len);
    return len;
}

v2d::Vector v2d::Vector::Normalize()
{
    double len = GetLength();
    return (*this / len);
}

v2d::Vector v2d::Vector::Rot(double theta)
{
    double rotx = (m_x * cos(theta)) - (m_y * sin(theta));
    double roty = (m_x * sin(theta)) + (m_y * cos(theta));

    return v2d::Vector(rotx, roty);
}

///////////////////////////////////////////////////////////////
//
//VectorClass//
    //v2d//
        //Point//

//Operators//
v2d::Vector v2d::Point::operator - (v2d::Point p)
{
    return Vector(this->m_x - p.GetX(), this->m_y - p.GetY());
}

v2d::Point v2d::Point::operator + (v2d::Vector v)
{
    return Point(this->m_x + v.GetX(), this->m_y + v.GetY());
}

v2d::Point v2d::Point::operator - (v2d::Vector v)
{
    return Point(this->m_x - v.GetX(), this->m_y - v.GetY());
}
///////////////////////////////////////////////////////////////
//
//VectorClass//
    //v3d//
        //Vector//

//Operators//
bool v3d::Vector::operator == (v3d::Vector v)
{
    if (this->m_x == v.GetX() && this->m_y == v.GetY() && this->m_z == v.GetZ())
    {
        return true;
    }
    return false;
}

v3d::Vector v3d::Vector::operator * (double mult)
{
    return Vector(this->m_x * mult, this->m_y * mult, this->m_z * mult);
}

v3d::Vector v3d::Vector::operator / (double div)
{
    return Vector(this->m_x / div, this->m_y / div, this->m_z / div);
}

v3d::Vector v3d::Vector::operator + (v3d::Vector v)
{
    return Vector(this->m_x + v.GetX(), this->m_y + v.GetY(), this->m_z + v.GetZ());
}

v3d::Vector v3d::Vector::operator - (v3d::Vector v)
{
    return Vector(this->m_x - v.GetX(), this->m_y - v.GetY(), this->m_z - v.GetZ());
}

v3d::Vector v3d::Vector::operator - ()
{
    return (*this * -1);
}

//Functions//
double v3d::Vector::Dot(v3d::Vector v)
{
    return (
        this->m_x * v.GetX() +
        this->m_y * v.GetY() +
        this->m_z * v.GetZ()
        );
}


double v3d::Vector::GetLength()
{
    double len = (pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));
    len = sqrt(len);
    return len;
}

v3d::Vector v3d::Vector::Cross(v3d::Vector v)
{
    double x = (this->GetY() * v.GetZ()) - (this->GetZ() * v.GetY());
    double y = (this->GetZ() * v.GetX()) - (this->GetX() * v.GetZ());
    double z = (this->GetX() * v.GetY()) - (this->GetY() * v.GetX());

    if (x == -0)
        x = 0.0;
    if (y == -0)
        y = 0.0;
    if (z == -0)
        z = 0.0;

    return v3d::Vector(x, y, z);
}

v3d::Vector v3d::Vector::Normalize()
{
    double len = GetLength();
    return (*this / len);
}

///////////////////////////////////////////////////////////////
//
//VectorClass//
    //v3d//
        //Point//

//Operators//
v3d::Vector v3d::Point::operator - (v3d::Point p)
{
    return Vector(this->m_x - p.GetX(), this->m_y - p.GetY(), this->m_z - p.GetZ());
}

v3d::Vector v3d::Point::operator >> (v3d::Point p)
{
    return (p - *this);
}

v3d::Vector v3d::Point::operator << (v3d::Point p)
{
    return (*this - p);
}

v3d::Point v3d::Point::operator + (v3d::Vector v)
{
    return Point(this->m_x + v.GetX(), this->m_y + v.GetY(), this->m_z + v.GetZ());
}

v3d::Point v3d::Point::operator - (v3d::Vector v)
{
    return Point(this->m_x - v.GetX(), this->m_y - v.GetY(), this->m_z - v.GetZ());
}

///////////////////////////////////////////////////////////////
