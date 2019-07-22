#include "Obstacle.h"

Obstacle::Obstacle(Point center_pos, Point size)
{
    m_min_corner = center_pos - size * 0.5;
    m_max_corner = center_pos + size * 0.5;
}

const Point Obstacle::getSize() const
{
    return m_max_corner - m_min_corner;
}

Obstacle::Obstacle(Object *object):Obstacle::Obstacle(object->getPosition(), object->getSize())
{

}