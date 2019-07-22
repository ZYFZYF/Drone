#ifndef DRONE_OBSTACLE_H
#define DRONE_OBSTACLE_H


#include "../../Common/utils/Point.h"
#include "../object/Object.h"

class Obstacle
{
public:
    explicit Obstacle(Object *object);
    Obstacle(Point center_pos, Point size);
    const Point getSize() const;
private:
    Point m_min_corner, m_max_corner;
};


#endif //DRONE_OBSTACLE_H
