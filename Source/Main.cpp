#include "GlobalHeaders.hpp"
#include "GlobalDefines.hpp"
#include "BitmapClass.hpp"
#include "VectorClass.hpp"
#include "LightClass.hpp"
#include "SortedLists.hpp"
#include "Objects.hpp"

namespace sllSphere = SortedLLists::SphereIntersect;
namespace OC = Objects::Concepts;
namespace OP = Objects::Physical;
namespace Vect3D = VectorClass::v3d;

#include <fstream>

// Far from optimized...
int main()
{
    const unsigned short screenWidth(500), screenHeight(500), numSpheres(5);

    // == Bitmap data == //
    Bitmap bitmap(
        "VectorTest.bmp",
        screenWidth,
        screenHeight,
        24
        );

    // == Sphere data == //
    OP::Sphere spheres[numSpheres] =
    {
        OP::Sphere(
                Vect3D::Point(0, 0, 400),
                RGBData(0x09, 0x04, 0x06),
                200.0
                ),
        OP::Sphere(
                Vect3D::Point(75, 0, 225),
                RGBData(0x00, 0x03, 0x0A),
                100.0
                ),
        OP::Sphere(
                Vect3D::Point(-100, 80, 250),
                RGBData(0x06, 0x04, 0x07),
                75.0
                ),
        OP::Sphere(
                Vect3D::Point(200, -80, 550),
                RGBData(0x05, 0x05, 0x05),
                300.0
                ),
        OP::Sphere(
                Vect3D::Point(90, -75, 90),
                RGBData(0x02, 0x09, 0x03),
                10.0
                ),
        
    };

    // == Light data == //
    OC::Lights::AmbientLight ambientLight(0, RGBData(0x00, 0x05, 0x00, 0xff));

    OC::Lights::PointLight pointLight(
                               Vect3D::Point(100, -75, 50),
                               3,
                               RGBData(0x05, 0x05, 0x05, 0xFF)
                               );

    // == Screen data == //
    OC::Core::Screen screen(Vect3D::Point(0, 0, 100), screenWidth, screenHeight);
    RGBData rgbData;


    // == Camera data == //
    OC::Core::Camera camera(Vect3D::Point(0, 0, 0));
    camera.AttachScreen(screen);

    // == Ray data == //
    // pointDot: Dot product point
    Vect3D::Point pointDot(0, 0, 0);
    OC::Core::Ray mainRay;
    mainRay.SetPointFrom(camera.GetPoint());

    //
    // -- Math Logic --
    // * Note: Variable names not meant to perfectly represent variables used in code
    //
    // vY = up
    // vX = (vV x vY) / ||(vV x vY)||
    //
    // vY(vScreenY) = vCameraUp
    // vX(vScreenX) = (vCameraAt x vCameraUp) / ||(vCameraAt x vCameraUp)||
    //
    // Point = Origin + (X * vX) + (Y * vY)
    // pointTo = pointAt + (X * vScreenX) + (Y * vScreenY)
    // 

    Vect3D::Point pointToReturn;
    pointToReturn = (
              screen.GetPoint() 
           - (camera.GetVectorX() * ((double)screenWidth / 2))
           + (camera.GetVectorY() * ((double)screenHeight / 2))
           );

    // This essentially shifts over and down by half a pixel and
    // provides a pointTo coordinate that represents the pixel center.
    pointToReturn = pointToReturn + ((camera.GetVectorX() * 0.5) + (camera.GetVectorY() * -0.5));
    mainRay.SetPointTo(pointToReturn);

    bool applyLighting(true);

    for (int row = 0; row < screenHeight; row++)
    {
        for (int col = 0; col < screenWidth; col++)
        {
            double closestSurface;
            bool firstIntersect;

            closestSurface = 0;
            firstIntersect = true;

            // == Core of the mainRay-tracer == //
            // - Sphere intersect - //
            for (int i = 0; i < numSpheres; i++)
            {
                if (spheres[i].FindIntersections(camera.GetPoint(), mainRay.GetVector()))
                {
                    if (firstIntersect)
                    {
                        closestSurface = (spheres[i].GetFrontIntersect() - camera.GetPoint()).GetLength();
                        firstIntersect = false;
                    }
                    else if ((spheres[i].GetFrontIntersect() - camera.GetPoint()).GetLength() < closestSurface)
                    {
                        closestSurface = (spheres[i].GetFrontIntersect() - camera.GetPoint()).GetLength();
                    }
                }
            }

            // Set initial color to black
            rgbData.blue = 0x00;
            rgbData.green = 0x00;
            rgbData.red = 0x00;
            rgbData.alpha = 0xFF;

            // - Lighting - //
            for (int i = 0; i < numSpheres; i++)
            {
                applyLighting = true;
                
                // Check for intersection
                if (spheres[i].Intersected(camera.GetPoint(), mainRay.GetVector()))
                {
                    if ((spheres[i].GetFrontIntersect() - camera.GetPoint()).GetLength() == closestSurface)
                    {
                        spheres[i].GetFrontIntersect();
                        pointLight.LightSurface(spheres, numSpheres, i, rgbData);

                        if ((rgbData.red + ambientLight.GetRed() * (_BYTE)ambientLight.GetLuminosity()) <= 254)
                        rgbData.red += ambientLight.GetRed() * (_BYTE)ambientLight.GetLuminosity();

                        if ((rgbData.blue + ambientLight.GetBlue() * (_BYTE)ambientLight.GetLuminosity()) <= 254)
                            rgbData.blue += ambientLight.GetBlue() * (_BYTE)ambientLight.GetLuminosity();

                        if ((rgbData.green + ambientLight.GetGreen() * (_BYTE)ambientLight.GetLuminosity()) <= 254)
                            rgbData.green += ambientLight.GetGreen() * (_BYTE)ambientLight.GetLuminosity();
                    }
                }
            }

            screen.SetPixel(rgbData, row, col);
            mainRay.MovePointTo(camera.GetVectorX());
        }
        pointToReturn = pointToReturn - camera.GetVectorY();
        mainRay.SetPointTo(pointToReturn);
    }

    // Initialize and print bitmap image.
    bitmap.Initialize();

    for (int row = 0; row < screenHeight; row++)
    {
        for (int col = 0; col < screenWidth; col++)
        {
            bitmap.Print(&screen.GetPixel(row, col));
        }
    }

	return 0;
}