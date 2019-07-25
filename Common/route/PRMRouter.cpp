#include "PRMRouter.h"

const int SCATTER_POINT_NUM = Config::Instance()->getIntParam("PRMRouter", "SCATTER_POINT_NUM");
std::vector<Point> PRMRouter::route(const Point &start_pos, const Point &end_pos)
{
    std::vector<Point> nodes{};
    nodes.emplace_back(start_pos);
    for(int i = 0; i < SCATTER_POINT_NUM; i ++)
    {
        nodes.emplace_back()
    }
    return std::vector<Point>();
}
