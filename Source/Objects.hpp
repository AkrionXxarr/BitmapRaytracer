#ifndef _OBJECTS_HPP_
#define _OBJECTS_HPP_

#include "GlobalDefines.hpp"
#include "VectorClass.hpp"
#include "SortedLists.hpp"

#include <vector>
#include <iostream>

namespace Objects
{
    namespace Abstract
    {
        class Color;
        class SpatialData;
    };

    namespace Concepts
    {
        namespace Core
        {
            class Camera;
            class Screen;
            class Ray;
            class Polygon;
        };

        namespace Lights
        {
            class Light;
            class AmbientLight;
            class PointLight;
        };
    };

    namespace Physical
    {
        class Sphere;
    };
};


namespace Objects
{
    namespace Abstract
    {
        class Color
        {
        public:
            //Get//
            virtual _BYTE GetRed() { return m_rgbData.red; }
            virtual _BYTE GetBlue() { return m_rgbData.blue; }
            virtual _BYTE GetGreen() { return m_rgbData.green; }
            virtual _BYTE GetAlpha() { return m_rgbData.alpha; }
            virtual RGBData GetRGBData() { return m_rgbData; }

            //Set//
            virtual void SetRed(_BYTE red) { m_rgbData.red = red; }
            virtual void SetBlue(_BYTE blue) { m_rgbData.blue = blue; }
            virtual void SetGreen(_BYTE green) { m_rgbData.green = green; }
            virtual void SetAlpha(_BYTE alpha) { m_rgbData.alpha = alpha; }

        protected:
            Color(RGBData rgbData) : m_rgbData(rgbData) { }

        private:
            RGBData m_rgbData;
        };

        class SpatialData
        {
        public:

            //Get//
            virtual VectorClass::v3d::Point GetPoint();
            virtual VectorClass::v3d::Vector GetVectorX();
            virtual VectorClass::v3d::Vector GetVectorY();
            virtual VectorClass::v3d::Vector GetVectorZ();

            //Set//
            virtual void SetPoint(VectorClass::v3d::Point p);
            virtual void SetVectorX(VectorClass::v3d::Vector v);
            virtual void SetVectorY(VectorClass::v3d::Vector v);
            virtual void SetVectorZ(VectorClass::v3d::Vector v);

        protected:
            //Constructors//
            SpatialData();
            SpatialData(SpatialData& spatialData);
            SpatialData(
                VectorClass::v3d::Point point,
                VectorClass::v3d::Vector xVector,
                VectorClass::v3d::Vector yVector,
                VectorClass::v3d::Vector zVector
                );
            SpatialData(VectorClass::v3d::Point point);
            SpatialData(
                VectorClass::v3d::Vector xVector,
                VectorClass::v3d::Vector yVector,
                VectorClass::v3d::Vector zVector
                );

            //Destructor//
            ~SpatialData();

            //Get Functions//
            bool GotPoint() { return m_gotPoint; }
            bool GotVectors() { return m_gotVectors; }

        private:
            VectorClass::v3d::Point* m_point;

            VectorClass::v3d::Vector* m_xVector;
            VectorClass::v3d::Vector* m_yVector;
            VectorClass::v3d::Vector* m_zVector;

            bool m_gotPoint;
            bool m_gotVectors;
        };
    };

    namespace Concepts
    {
        //////////
        // Core //
        //////////
        namespace Core
        {          
            // == Camera == //
            class Camera : public Objects::Abstract::SpatialData
            {
            public:
                Camera(
                    VectorClass::v3d::Point point
                    ) : m_distFromScreen(0.0),
                        Objects::Abstract::SpatialData(
                                                    point,
                                                    VectorClass::v3d::Vector(),
                                                    VectorClass::v3d::Vector(),
                                                    VectorClass::v3d::Vector()
                                                    ) { }

                void AttachScreen(Objects::Concepts::Core::Screen& screen);

                //Get//
                double GetScreenDistance() { return m_distFromScreen; }

            private:
                double m_distFromScreen;
            };
        
            // == Screen == //
            class Screen : public Objects::Abstract::SpatialData
            {
            public:
                Screen(
                    VectorClass::v3d::Point point,
                    unsigned int width,
                    unsigned int height
                    );

                //Get//
                unsigned int GetWidth() { return m_width; }
                unsigned int GetHeight() { return m_height; }
                RGBData GetPixel(unsigned int row, unsigned int col);

                //Set//
                void SetPixel(RGBData rgbData, unsigned int row, unsigned int col);

            private:
                unsigned int m_width, m_height;
                std::vector<std::vector<RGBData> > m_screenData;
            };

            // == Ray == //
            class Ray
            {
            public:
                Ray();
                Ray(VectorClass::v3d::Point pointFrom, VectorClass::v3d::Point pointTo);
                Ray(Ray& ray);
                ~Ray();

                //Get//
                VectorClass::v3d::Vector GetVector();
                VectorClass::v3d::Point GetPointFrom() { return *m_pointFrom; }
                VectorClass::v3d::Point GetPointTo() { return *m_pointTo; }

                //Move//
                void MovePointFrom(VectorClass::v3d::Vector v) { *m_pointFrom = *m_pointFrom + v; }
                void MovePointTo(VectorClass::v3d::Vector v) { *m_pointTo = *m_pointTo + v; }

                //Set//
                void SetPointFrom(VectorClass::v3d::Point p) { *m_pointFrom = p; }
                void SetPointTo(VectorClass::v3d::Point p) { *m_pointTo = p; }

            private:
                VectorClass::v3d::Point* m_pointFrom;
                VectorClass::v3d::Point* m_pointTo;
                VectorClass::v3d::Vector* m_vector;
            };

            // == Polygon == //
            class Polygon : public Objects::Abstract::Color
            {
            public:
                Polygon();
                Polygon(RGBData rgbData);
                Polygon(Polygon& poly);
                ~Polygon();

                bool FoundIntersections() { return m_foundIntersections; }

                virtual bool Intersected(VectorClass::v3d::Point& p, VectorClass::v3d::Vector& v) = 0;
                virtual bool FindIntersections(VectorClass::v3d::Point& p, VectorClass::v3d::Vector& v) = 0;

                virtual VectorClass::v3d::Vector GetNormal(VectorClass::v3d::Point p) = 0;
                virtual VectorClass::v3d::Point GetFrontIntersect() { return *m_frontIntersect; }
                virtual VectorClass::v3d::Point GetBackIntersect() { return *m_backIntersect; }

            protected:
                void SetFrontIntersect(VectorClass::v3d::Point p) { *m_frontIntersect = p; }
                void SetBackIntersect(VectorClass::v3d::Point p) { *m_backIntersect = p; }
                void FoundIntersections(bool b) { m_foundIntersections = b; }

            private:
                bool m_foundIntersections;
                VectorClass::v3d::Point* m_frontIntersect;
                VectorClass::v3d::Point* m_backIntersect;
                Polygon* m_next;
            };
        };

        ////////////
        // Lights //
        ////////////
        namespace Lights
        {
            class Light : public Objects::Abstract::Color
            {
            public:
                Light(double luminosity, RGBData rgbData) : Objects::Abstract::Color(rgbData),
                                                            m_luminosity(luminosity) { }

                virtual bool LightSurface(
                                      Objects::Concepts::Core::Polygon* polyArray,
                                      unsigned int numOfPolygons,
                                      unsigned int currentIndex,
                                      RGBData& rgbData
                                      ) = 0;

                double GetLuminosity() { return m_luminosity; }

            private:
                double m_luminosity;
                
            };

            class AmbientLight : public Objects::Abstract::Color
            {
            public:
                AmbientLight(double luminosity, RGBData rgbData) : Objects::Abstract::Color(rgbData),
                                                                   m_luminosity(luminosity) { }

                double GetLuminosity() { return m_luminosity; }
            private:
                double m_luminosity;
            };

            class PointLight : public Objects::Concepts::Lights::Light,
                               public Objects::Abstract::SpatialData 
            {
            public:
                PointLight (
                    VectorClass::v3d::Point point,
                    double luminosity,
                    RGBData rgbData
                    ) : Objects::Concepts::Lights::Light(luminosity, rgbData),
                        Objects::Abstract::SpatialData(point) { }

                bool LightSurface(
                              Objects::Concepts::Core::Polygon* polyArray,
                              unsigned int numOfPolygons,
                              unsigned int currentIndex,
                              RGBData& rgbData
                              );

            };
        };
    };

    namespace Physical
    {
        class Sphere : public Objects::Concepts::Core::Polygon,
                       public Objects::Abstract::SpatialData
        {
        public:
            Sphere(
                VectorClass::v3d::Point point,
                RGBData rgbData,
                double radius
                ) : m_radius(radius),
                    Objects::Concepts::Core::Polygon(rgbData),
                    Objects::Abstract::SpatialData(point) { }
            Sphere(
                VectorClass::v3d::Point point,
                VectorClass::v3d::Vector xVector,
                VectorClass::v3d::Vector yVector,
                VectorClass::v3d::Vector zVector,
                RGBData rgbData,
                double radius
                ) : m_radius(radius),
                    Objects::Concepts::Core::Polygon(rgbData),
                    Objects::Abstract::SpatialData(
                                                point,
                                                xVector,
                                                yVector,
                                                zVector
                                                ) { }

            bool Intersected(VectorClass::v3d::Point& p, VectorClass::v3d::Vector& v);
            bool FindIntersections(VectorClass::v3d::Point& p, VectorClass::v3d::Vector& v);

            double GetRadius() { return m_radius; }
            VectorClass::v3d::Vector GetNormal(VectorClass::v3d::Point p)
            {
                VectorClass::v3d::Vector v = p - GetPoint();
                v = v.Normalize();
                return v;
            }

        private:
            double m_radius;
        };
    };
};

#endif