#include "NaiveRouter.h"

std::vector<Point> NaiveRouter::route(const Point &start_pos, const Point &end_pos)
{
    //加个中点
    std::vector<Point> ret;
    ret.emplace_back(start_pos);
    ret.emplace_back((start_pos + end_pos) / 2);
    ret.emplace_back(end_pos);
    return ret;
}
