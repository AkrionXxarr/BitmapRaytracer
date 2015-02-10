#include "Objects.hpp"

namespace OA = Objects::Abstract;
namespace OC = Objects::Concepts;
namespace OP = Objects::Physical;

namespace Vect = VectorClass::v3d;
///////////////////////////////////////////////////////////////
//
//Objects//
    //Abstract//
        //SpatialData//

//Default Constructor//
OA::SpatialData::SpatialData()
{
    m_point = new Vect::Point();

    m_xVector = new Vect::Vector();
    m_yVector = new Vect::Vector();
    m_zVector = new Vect::Vector();

    m_gotPoint = true;
    m_gotVectors = true;
}

//Copy Constructor//
OA::SpatialData::SpatialData(SpatialData& spatialData)
{
    m_gotPoint = false;
    m_gotVectors = false;

    if (spatialData.GotPoint())
    {
        m_point = new Vect::Point();
        *m_point = *spatialData.m_point;
        m_gotPoint = true;
    }

    if (spatialData.GotVectors())
    {
        m_xVector = new Vect::Vector();
        m_yVector = new Vect::Vector();
        m_zVector = new Vect::Vector();

        *m_xVector = *spatialData.m_xVector;
        *m_yVector = *spatialData.m_yVector;
        *m_zVector = *spatialData.m_zVector;

        m_gotVectors = true;
    }
}

//Parameter Constructors//
OA::SpatialData::SpatialData(Vect::Point point)
{
    m_point = new Vect::Point(point);

    m_xVector = NULL;
    m_yVector = NULL;
    m_zVector = NULL;

    m_gotPoint = true;
    m_gotVectors = false;
}

OA::SpatialData::SpatialData(
                    Vect::Vector xVector,
                    Vect::Vector yVector,
                    Vect::Vector zVector
                    )
{
    m_point = NULL;

    m_xVector = new Vect::Vector(xVector);
    m_yVector = new Vect::Vector(yVector);
    m_zVector = new Vect::Vector(zVector);

    m_gotPoint = false;
    m_gotVectors = true;
}
                             

OA::SpatialData::SpatialData(
                     Vect::Point point, 
                     Vect::Vector xVector, 
                     Vect::Vector yVector,
                     Vect::Vector zVector
                     )
{
    m_point = new Vect::Point(point);

    m_xVector = new Vect::Vector(xVector);
    m_yVector = new Vect::Vector(yVector);
    m_zVector = new Vect::Vector(zVector);

    m_gotPoint = true;
    m_gotVectors = true;
}

//Destructor//
OA::SpatialData::~SpatialData()
{
    if (m_gotPoint)
    {
        delete m_point;
    }

    if (m_gotVectors)
    {
        delete m_xVector;
        delete m_yVector;
        delete m_zVector;
    }
}

//Set Functions//
void OA::SpatialData::SetPoint(Vect::Point p)
{
    if (m_gotPoint)
        *m_point = p;
}

void OA::SpatialData::SetVectorX(Vect::Vector v)
{
    if (m_gotVectors)
        *m_xVector = v;
}

void OA::SpatialData::SetVectorY(Vect::Vector v)
{
    if (m_gotVectors)
        *m_yVector = v;
}

void OA::SpatialData::SetVectorZ(Vect::Vector v)
{
    if (m_gotVectors)
        *m_zVector = v;
}

//Get Functions//
Vect::Point OA::SpatialData::GetPoint()
{
    if (m_gotPoint)
        return *m_point;
    else
        return Vect::Point();
}

Vect::Vector OA::SpatialData::GetVectorX()
{
    if (m_gotVectors)
        return *m_xVector;
    else
        return Vect::Vector();
}

Vect::Vector OA::SpatialData::GetVectorY()
{
    if (m_gotVectors)
        return *m_yVector;
    else
        return Vect::Vector();
}

Vect::Vector OA::SpatialData::GetVectorZ()
{
    if (m_gotVectors)
        return *m_zVector;
    else
        return Vect::Vector();
}

////
////
////
////
////
////
////
////
////
////

///////////////////////////////////////////////////////////////
//
//Objects//
    //Concept//
        //Core//
            //Camera//

//Functions//

// Problem: ~SpatialData gets called on leaving Initialize function
// Solution: 'OC::Screen screen' was being used for the argument,
//           this caused an initialization of a new screen object
//           to the same location, resulting in the memory being
//           deleted out from under the object being passed in.
//           Changing to pass by reference fixed the problem.
void OC::Core::Camera::AttachScreen(OC::Core::Screen& screen)
{
    Vect::Vector yVector;
    Vect::Vector zVector;
    Vect::Vector vTemp;

    zVector = screen.GetPoint() - GetPoint();
    vTemp = Vect::Vector(0, 1, 0).Cross(zVector);

    if (vTemp.GetLength() == 0)
    {
        yVector.SetVector(0, 0, 1);
    }
    else
    {
        yVector = zVector.Cross(vTemp);
    }

    m_distFromScreen = zVector.GetLength();
    SetVectorX(yVector.Cross(zVector).Normalize());
    SetVectorY(yVector.Normalize());
    SetVectorZ(zVector.Normalize());
}

///////////////////////////////////////////////////////////////
//
//Objects//
    //Concept//
        //Core//
            //Screen//

//Constructor//
OC::Core::Screen::Screen(
                        VectorClass::v3d::Point point,
                        unsigned int width,
                        unsigned int height
                        ) : Objects::Abstract::SpatialData(point),
                            m_width(width),
                            m_height(height) 
{
    m_screenData.resize(height, std::vector<RGBData>(width));
}

//Set Functions//
void OC::Core::Screen::SetPixel(RGBData rgbData, unsigned int row, unsigned int col)
{
    m_screenData.at(row).at(col) = rgbData;
}

//Get Functions//
RGBData OC::Core::Screen::GetPixel(unsigned int row, unsigned int col)
{
    return m_screenData.at(row).at(col);
}

///////////////////////////////////////////////////////////////
//
//Objects//
    //Concept//
        //Core//
            //Ray//

//Default Constructor//
OC::Core::Ray::Ray()
{
    m_pointFrom = new Vect::Point();
    m_pointTo = new Vect::Point();
    m_vector = new Vect::Vector();
}

//Parameter Constructor//
OC::Core::Ray::Ray(VectorClass::v3d::Point pointFrom, VectorClass::v3d::Point pointTo)
{
    m_pointFrom = new Vect::Point(pointFrom);
    m_pointTo = new Vect::Point(pointTo);
    m_vector = new Vect::Vector(GetVector());
}

//Copy Constructor//
OC::Core::Ray::Ray(Ray& ray)
{
    m_pointFrom = new Vect::Point();
    m_pointTo = new Vect::Point();
    m_vector = new Vect::Vector();

    *m_pointFrom = *ray.m_pointFrom;
    *m_pointTo = *ray.m_pointTo;
    *m_vector = *ray.m_vector;
}

//Destructor//
OC::Core::Ray::~Ray()
{
    delete m_pointFrom;
    delete m_pointTo;
    delete m_vector;
}

//Get Functions//
Vect::Vector OC::Core::Ray::GetVector()
{
    return (*m_pointTo - *m_pointFrom);
}

///////////////////////////////////////////////////////////////
//
//Objects//
    //Concept//
        //Core//
            //Polygon//

//Default Constructor//
OC::Core::Polygon::Polygon() : OA::Color(RGBData(0, 0, 0, 0)), m_foundIntersections(false)
{
    m_frontIntersect = new Vect::Point();
    m_backIntersect = new Vect::Point();
}

//Parameter Constructor//
OC::Core::Polygon::Polygon(RGBData rgbData) : OA::Color(rgbData), m_foundIntersections(false)
{
    m_frontIntersect = new Vect::Point();
    m_backIntersect = new Vect::Point();
}

//Copy Constructor//
OC::Core::Polygon::Polygon(Polygon& poly) : OA::Color(poly.GetRGBData()), m_foundIntersections(false)
{
    m_frontIntersect = new Vect::Point();
    m_backIntersect = new Vect::Point();

    *m_frontIntersect = *poly.m_frontIntersect;
    *m_backIntersect = *poly.m_backIntersect;
}

//Destructor//
OC::Core::Polygon::~Polygon()
{
    delete m_frontIntersect;
    delete m_backIntersect;
}

//
//
//
//

///////////////////////////////////////////////////////////////
//
//Objects//
    //Concept//
        //Lights//
            //Light//

///////////////////////////////////////////////////////////////
//
//Objects//
    //Concept//
        //Lights//
            //Point//

//Functions//
bool OC::Lights::PointLight::LightSurface(
                                      OC::Core::Polygon* polyArray, 
                                      unsigned int numOfPolygons, 
                                      unsigned int currentIndex,
                                      RGBData& rgbData
                                      )
{
    Vect::Vector vNormal;
    Vect::Vector vLight;

    OP::Sphere* sphereArray = (OP::Sphere*) polyArray;

    bool applyLighting(true);
    double red(0x00), blue(0x00), green(0x00);
    double saturation(0.0);

    if (currentIndex >= numOfPolygons)
    {
        return false;
    }
    else if (sphereArray[currentIndex].FoundIntersections())
    {
        sphereArray[currentIndex].GetFrontIntersect();
        vNormal = sphereArray[currentIndex].GetNormal(sphereArray[currentIndex].GetFrontIntersect());
        vLight = (GetPoint() - sphereArray[currentIndex].GetFrontIntersect()).Normalize();

        for (unsigned int i = 0; i < numOfPolygons; i++)
        {
            if (sphereArray[i].Intersected(sphereArray[currentIndex].GetFrontIntersect(), vLight))
            {
                applyLighting = false;
                break;
            }
        }

        if (applyLighting)
        {
            red = (double)sphereArray[currentIndex].GetRed();
            blue = (double)sphereArray[currentIndex].GetBlue();
            green = (double)sphereArray[currentIndex].GetGreen();

            saturation = vNormal.Dot(vLight);
            if (saturation < 0.0) { saturation = 0.0; }
            else if (saturation > 1.0) { saturation = 1.0; }

            red *= (double)GetRed() * saturation;
            blue *= (double)GetBlue() * saturation;
            green *= (double)GetGreen() * saturation;

            red *= GetLuminosity();
            blue *= GetLuminosity();
            green *= GetLuminosity();

            if (blue > 254.0)
                blue = 254.0;
            else if (blue < 0.0)
                blue = 0.0;

            if (green > 254.0)
                green = 254.0;
            else if (green < 0.0)
                green = 0.0;

            if (red > 254.0)
                red = 254.0;
            else if (red < 0.0)
                red = 0.0;
        }

        rgbData.red = (_BYTE)Round(red);
        rgbData.blue = (_BYTE)Round(blue);
        rgbData.green = (_BYTE)Round(green);

        return true;
    }
    return false;
}



////
////
////
////
////
////
////
////
////
////

///////////////////////////////////////////////////////////////
//
//Objects//
    //Physical//
        //Sphere//

//Functions//
bool OP::Sphere::Intersected(Vect::Point& p, Vect::Vector& v)
{
    Vect::Point pointDot;
    double dotCheck(0);

    v = v.Normalize();

    pointDot = p + (v * (GetPoint() - p).Dot(v));
    dotCheck = (pointDot - GetPoint()).GetLength();

    // Checks the length of the point moved along the vector v
    // If the point is behind the vector, the length will become shorter,
    // Otherwise it'll become longer.
    if (((pointDot + v) - p).GetLength() < (pointDot - p).GetLength())
    {
        return false;
    }
    else if ((GetPoint() - p).GetLength() == 0)
    {
        return false;
    }
    else if  (dotCheck <= m_radius)
    {
        return true;
    }

    return false;
}

bool OP::Sphere::FindIntersections(Vect::Point& p, Vect::Vector& v)
{
    Vect::Point pointDot;
    double dotCheck(0);

    SetFrontIntersect(Vect::Point(0, 0, 0));
    SetBackIntersect(Vect::Point(0, 0, 0));

    pointDot = p + (v.Normalize() * (GetPoint() - p).Dot(v.Normalize()));
    dotCheck = (pointDot - GetPoint()).GetLength();

    if (Intersected(p, v))
    {
        if (dotCheck == m_radius)
        {
            SetFrontIntersect(pointDot);
            SetBackIntersect(pointDot);
        }
        else if (dotCheck < m_radius)
        {
            double a(0), b(0), c(0);

            a = pow(dotCheck, 2.0);
            c = pow(m_radius, 2.0);
            b = sqrt(c - a);

            SetFrontIntersect(pointDot - (v.Normalize() * b));
            SetBackIntersect(pointDot + (v.Normalize() * b));
        }

        FoundIntersections(true);
        return true;
    }
    FoundIntersections(false);
    return false;
}