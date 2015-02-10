#ifndef _LIGHT_CLASS_HPP_
#define _LIGHT_CLASS_HPP_

#include "BitmapClass.hpp"
#include "VectorClass.hpp"

class Light
{
public:
    Light (
        double x, 
        double y, 
        double z, 
        double luminosity
        );
    ~Light();

    VectorClass::v3d::Point GetPoint()
    {
        return *m_point;
    }

    _BYTE GetRed() { return m_rgbdata.red; }
    _BYTE GetBlue() { return m_rgbdata.blue; }
    _BYTE GetGreen() { return m_rgbdata.green; }
    _BYTE GetAlpha() { return m_rgbdata.alpha; }

    double GetLuminosity() { return m_luminosity; }

    void SetRed(_BYTE red) { m_rgbdata.red = red; }
    void SetBlue(_BYTE blue) { m_rgbdata.blue = blue; }
    void SetGreen(_BYTE green) { m_rgbdata.green = green; }
    void SetAlpha(_BYTE alpha) { m_rgbdata.alpha = alpha; }

private:
    double m_luminosity;
    RGBData m_rgbdata;
    VectorClass::v3d::Vector *m_vector;
    VectorClass::v3d::Point *m_point;
};

#endif