#ifndef _SORTED_LIST_HPP_
#define _SORTED_LIST_HPP_

#include "SphereClass.hpp"
#include "VectorClass.hpp"
#include "Objects.hpp"

namespace SortedLList
{
    namespace Polygons
    {
        struct lPolygon;
    };
};

namespace SortedLLists
{
    namespace Polygons
    {
        struct lPolygon
        {

            lPolygon* m_next;
            lPolygon* m_last;
        };

        class PolygonList
        {
        public:

        private:
            lPolygon* m_head;
            lPolygon* m_tail;
            lPolygon* m_iterator;
        };
    }

    namespace SphereIntersect
    {
        struct lIntersect
        {
            lIntersect(VectorClass::v3d::Point point, double distance, int sphereID);
            ~lIntersect();

            double m_distance;
            int m_sphereID;
            VectorClass::v3d::Point* m_point;
            lIntersect* m_next;
            lIntersect* m_last;
        };

        class IntersectList
        {
        public:
            IntersectList(VectorClass::v3d::Point pointFrom);
            ~IntersectList();

            void AddIntersect(VectorClass::v3d::Point point, int sphereID);
            void ClearList();

            int GetFurthest();
            int GetClosest();
            double GetDistance(int sphereID);
            VectorClass::v3d::Point* GetIntersectPoint(int sphereID);

            void SetPointFrom(VectorClass::v3d::Point point);


        private:
            VectorClass::v3d::Point* m_pointFrom;
            lIntersect* m_head;
            lIntersect* m_tail;
            lIntersect* m_iterator;
        };
    };
};
#endif