#ifndef _SPHERE_CLASS_HPP_
#define _SPHERE_CLASS_HPP_

#include "GlobalDefines.hpp"
#include "VectorClass.hpp"

class Sphere
{
public:
    Sphere(
        double x, 
        double y, 
        double z, 
        double radius
        );
    ~Sphere();

    double GetRadius() { return m_radius; }

    VectorClass::v3d::Point GetPoint()
    {
        return *m_point;
    }

    VectorClass::v3d::Vector Normal(VectorClass::v3d::Point p)
    {
        VectorClass::v3d::Vector v = p - *m_point;
        v = v.Normalize();
        return v;
    }

    _BYTE GetRed() { return m_rgbdata.red; }
    _BYTE GetBlue() { return m_rgbdata.blue; }
    _BYTE GetGreen() { return m_rgbdata.green; }
    _BYTE GetAlpha() { return m_rgbdata.alpha; }

    void SetRed(_BYTE red) { m_rgbdata.red = red; }
    void SetBlue(_BYTE blue) { m_rgbdata.blue = blue; }
    void SetGreen(_BYTE green) { m_rgbdata.green = green; }
    void SetAlpha(_BYTE alpha) { m_rgbdata.alpha = alpha; }

private:
    double m_radius;
    RGBData m_rgbdata;
    VectorClass::v3d::Point *m_point;
};

#endif
