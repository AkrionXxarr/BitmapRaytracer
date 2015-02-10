#ifndef _VECTOR_CLASS_HPP_
#define _VECTOR_CLASS_HPP_

#define _USE_MATH_DEFINES
#include <math.h>


namespace VectorClass
{
    namespace v2d
    {
        class Vector
        {
        public:
            Vector() : m_x(0), m_y(0) { }
            Vector(double x, double y) : m_x(x), m_y(y) { }

            Vector operator * (double mult);
            Vector operator / (double div);
            Vector operator + (Vector v);
            Vector operator - (Vector v);
            Vector operator - ();

            double GetLength();
            double GetX() { return m_x; }
            double GetY() { return m_y; }

            double Dot(Vector v);
            void SetVector(double x, double y) { m_x = x; m_y = y; }
            //void SetX(double x) { m_x = x; }
            //void SetY(double y) { m_y = y; }

            Vector Normalize();
            Vector Rot(double theta);

        private:
            double m_x, m_y;
        };

        class Point
        {
        public:
            Point() : m_x(0), m_y(0) { }
            Point(double x, double y) : m_x(x), m_y(y) { }

            Vector operator - (Point p);

            Point operator + (Vector v);
            Point operator - (Vector v);

            double GetX() { return m_x; }
            double GetY() { return m_y; }

            void SetPoint(double x, double y) { m_x = x; m_y = y; }
            void SetX(double x) { m_x = x; }
            void SetY(double y) { m_y = y; }

        private:
            double m_x, m_y;
        };
    };

    namespace v3d
    {
        class Vector
        {
        public:
            Vector() : m_x(0), m_y(0), m_z(0) { }
            Vector(double x, double y, double z) : m_x(x), m_y(y), m_z(z) { }

            bool operator == (Vector v);
            Vector operator * (double mult);
            Vector operator / (double div);
            Vector operator + (Vector v);
            Vector operator - (Vector v);
            Vector operator - ();

            double Dot(Vector v2);
            double GetLength();
            double GetX() { return m_x; }
            double GetY() { return m_y; }
            double GetZ() { return m_z; }

            void SetVector(double x, double y, double z) { m_x = x; m_y = y; m_z = z; }
            //void SetX(double x) { m_x = x; }
            //void SetY(double y) { m_y = y; }

            Vector Cross(Vector v);
            Vector Normalize();

        private:
            double m_x, m_y, m_z;
        };

        class Point
        {
        public:
            Point() : m_x(0), m_y(0), m_z(0) { }
            Point(double x, double y, double z) : m_x(x), m_y(y), m_z(z) { }

            Vector operator - (Point p);
            Vector operator >> (Point p);
            Vector operator << (Point p);

            Point operator + (Vector v);
            Point operator - (Vector v);

            double GetX() { return m_x; }
            double GetY() { return m_y; }
            double GetZ() { return m_z; }

            void SetPoint(double x, double y, double z) { m_x = x; m_y = y; m_z = z; }
            void SetX(double x) { m_x = x; }
            void SetY(double y) { m_y = y; }
            void SetZ(double z) { m_z = z; }

        private:
            double m_x, m_y, m_z;
        };
    };
};
#endif