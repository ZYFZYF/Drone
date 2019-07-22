#include <iostream>
#include "RRT.h"

int main()
{
    std::cout<<"Hello world\n";
    RRT rrt;
    rrt.addObstacle(Point(1, 1, 1), Point(2, 2, 2));
    std::vector<Point> route;
    auto success = rrt.generateRoute(Point(0, 0, 0), Point(3, 3, 3), route);
    std::cout << success;
    for (auto p:route)
    {
        printf("%.3lf %.3lf %.3lf\n", p.x(), p.y(), p.z());
    }
}