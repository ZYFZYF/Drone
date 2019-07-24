//
// Created by eric on 19-7-23.
//

#include "RRTRouter.h"
#include "../../Common/RRT/RRT.h"

std::vector<Point>
RRTRouter::route(const Point &start_pos, const Point &end_pos)
{
    RRT rrt;
    std::vector<Point> route, ret;

    for (const auto &obstacle: m_obstacles)
    {
        rrt.addObstacle(obstacle.getMinCorner(), obstacle.getMaxCorner());
    }
    rrt.generateRoute(start_pos, end_pos, route, 0.5);
    for (const auto &point: route)
    {
        printf("R: %.4lf %.4lf %.4lf\n", point.x(), point.y(), point.z());
    }
    for (int i = 0; i < m_obstacles.size(); ++i)
    {
        if (i % 4 == 0)
        {
            ret.push_back(route[i]);
        }
    }

    return ret;
}
