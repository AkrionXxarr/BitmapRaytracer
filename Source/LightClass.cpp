#include "LightClass.hpp"

Light::Light(double x, double y, double z, double luminosity) : m_luminosity(luminosity)
{
    m_vector = new VectorClass::v3d::Vector();
    m_point = new VectorClass::v3d::Point(x, y, z);
}

Light::~Light()
{
    delete m_vector;
    delete m_point;
}