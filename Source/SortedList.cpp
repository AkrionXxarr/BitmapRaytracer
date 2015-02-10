#include <iostream>
#include "SortedLists.hpp"

namespace sll = SortedLLists;
//namespace SLLPoly = SortedLLists::Polygons;
namespace sllSphere = SortedLLists::SphereIntersect;
namespace OC = Objects::Concepts;

short HEAD = -1;
short TAIL = -2;

///////////////////////////////////////////////////////////////
//
//SortedLLists//
    //IntersectList//

///////////////////////////////////////////////////////////////
//
//SortedLLists//
    //lIntersect//

//Constructor//
sllSphere::lIntersect::lIntersect(
                             VectorClass::v3d::Point point, 
                             double distance, 
                             int sphereID
                             ) : m_distance(distance), m_sphereID(sphereID)
{
    m_point = new VectorClass::v3d::Point(point);
}

//Destructor//
sllSphere::lIntersect::~lIntersect()
{
    delete m_point;
}

///////////////////////////////////////////////////////////////
//
//SortedLLists//
    //IntersectList//

//Constructor//
sllSphere::IntersectList::IntersectList(VectorClass::v3d::Point pointFrom)
{
    m_head = new lIntersect(VectorClass::v3d::Point(), HEAD, HEAD);
    m_tail = new lIntersect(VectorClass::v3d::Point(), TAIL, TAIL);
    m_pointFrom = new VectorClass::v3d::Point(pointFrom);

    m_head->m_next = m_tail;
    m_head->m_last = NULL;
    m_tail->m_next = NULL;
    m_tail->m_last = m_head;

    m_iterator = m_head;
}

//Deconstructor//
sllSphere::IntersectList::~IntersectList()
{
    m_iterator = m_head;

    while (m_iterator->m_next != NULL)
    {
        m_iterator = m_iterator->m_next;

        if (m_iterator->m_last != NULL)
        {
            delete m_iterator->m_last;
        }
    }

    delete m_pointFrom;
    delete m_iterator;
}

//Functions//
void sllSphere::IntersectList::AddIntersect(VectorClass::v3d::Point point, int sphereID)
{
    VectorClass::v3d::Vector v = point - *m_pointFrom;
    m_iterator = m_head;

    while (m_iterator->m_next != NULL)
    {
        m_iterator = m_iterator->m_next;

        if (v.GetLength() <= m_iterator->m_distance)
        {
            break;
        }
    }

    //////
    // -- Create a new Intersect struct and re-connect pointers
    // Make the last element's 'next' pointer point to a new element
    // Make the new element's 'last' pointer point back
    // Make the current element's 'last' pointer point at new element
    // Make the new element's 'next' pointer point at current element
    //////
    m_iterator->m_last->m_next = new lIntersect(point, v.GetLength(), sphereID);
    m_iterator->m_last->m_next->m_last = m_iterator->m_last;
    m_iterator->m_last = m_iterator->m_last->m_next;
    m_iterator->m_last->m_next = m_iterator;
}

void sllSphere::IntersectList::ClearList()
{
    m_iterator = m_head;

    while (m_iterator->m_next != NULL)
    {
        m_iterator = m_iterator->m_next;
        if (m_iterator->m_last != NULL && m_iterator->m_last != m_head)
        {
            delete m_iterator->m_last;
        }
    }

    m_head->m_next = m_tail;
    m_tail->m_last = m_head;
}

int sllSphere::IntersectList::GetClosest()
{
    m_iterator = m_head->m_next;

    if (m_iterator == m_tail)
    {
        return -1;
    }

    return m_iterator->m_sphereID;
}

int sllSphere::IntersectList::GetFurthest()
{
    m_iterator = m_tail->m_last;

    if (m_iterator == m_head)
    {
        return -1;
    }

    return m_iterator->m_sphereID;
}

double sllSphere::IntersectList::GetDistance(int sphereID)
{
    m_iterator = m_head;

    while (m_iterator->m_next != NULL && m_iterator->m_sphereID != sphereID)
    {
        m_iterator = m_iterator->m_next;
    }

    return m_iterator->m_distance;
}

VectorClass::v3d::Point* sllSphere::IntersectList::GetIntersectPoint(int sphereID)
{
    m_iterator = m_head;

    while (m_iterator->m_next != NULL && m_iterator->m_sphereID != sphereID)
    {
        m_iterator = m_iterator->m_next;
    }

    return m_iterator->m_point;
}

void sllSphere::IntersectList::SetPointFrom(VectorClass::v3d::Point point)
{
    *m_pointFrom = point;
}