#ifndef DRONE_ROUTER_H
#define DRONE_ROUTER_H


#include "Obstacle.h"

class Router
{
public:
    Router();
    void addObstacle(const Obstacle &obstacle);
    virtual std::vector<Point> route(const Point &start_pos, const Point &end_pos) = 0;

protected:
    std::vector<Obstacle> m_obstacles;
};


#endif //DRONE_ROUTER_H
