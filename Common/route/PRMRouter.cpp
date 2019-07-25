#include <queue>
#include "PRMRouter.h"
#include "../utils/utils.h"

const int SCATTER_POINT_NUM = Config::Instance()->getIntParam("PRMRouter", "SCATTER_POINT_NUM");
float dist[SCATTER_POINT_NUM];
int prevNode[SCATTER_POINT_NUM];

std::vector<Point> PRMRouter::route(const Point &start_pos, const Point &end_pos)
{
    std::vector<Point> nodes{};
    nodes.emplace_back(start_pos);
    for (int i = 0; i < SCATTER_POINT_NUM; i++)
    {
        nodes.emplace_back(utils::generateRandomPointBetween(start_pos, end_pos));
    }
    nodes.emplace_back(end_pos);
    auto n = nodes.size();
    auto s = 0, t = n - 1;
    std::priority_queue<std::pair<float, int> > q;
    q.push(std::make_pair(0, s));
    auto cnt = 0;
    while (!q.empty())
    {
        int x = q.top().second;
        if(cnt == n || x == t)break;
        for (int y = 0; y < n; y++)
        {
            if (!utils::existCollisionBetweenBaseAndObstacles(nodes[y], m_obstacles) &&
                !utils::existCollisionBetweenBaselineAndObstacles(nodes[x], nodes[y], m_obstacles) &&
                    dist[x] + distance(nodes[x], nodes[y]) < dist[y])
            {
                dist[y] = dist[x] + distance(nodes[x], nodes[y]);
                prevNode[y] = x;
                q.push(std::make_pair(dist[y], y));
            }
        }
    }
    auto ret = std::vector<Point>{};
    while(t)
    {
        ret.emplace_back(nodes[t]);
        t = prevNode[t];
    }
    ret.emplace_back(nodes[s]);
    std::reverse(ret.begin(), ret.end());
    return ret;
}
