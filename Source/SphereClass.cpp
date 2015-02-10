#include "SphereClass.hpp"

Sphere::Sphere(
        double x, 
        double y, 
        double z, 
        double radius
        ) : m_radius(radius) 
{
    m_point = new VectorClass::v3d::Point(x, y, z);
}

Sphere::~Sphere()
{
    delete m_point;
}