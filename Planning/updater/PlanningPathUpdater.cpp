#include <iostream>
#include <queue>
#include <algorithm>
#include "PlanningPathUpdater.h"
#include "../../Common/config/Config.h"
#include "../object/Object.h"
#include "../object/Door.h"
#include "../object/Tree.h"
#include "../object/Cylinder.h"
#include "../object/Joint.h"
#include "../object/Platform.h"
#include "../task/MoveTask.h"


using namespace std;
PlanningPathUpdater::PlanningPathUpdater(int client_id) : PlanningUpdater(
        Config::Instance()->getIntParam("PlanningPathUpdater", "TIME_STEP"), client_id)
{
    //can't get the first object's info
    Object trash("nothing", client_id);
    vector<string> doors = Config::Instance()->getStringVectorParam("PlanningPathUpdater", "DOOR");
    vector<string> trees = Config::Instance()->getStringVectorParam("PlanningPathUpdater", "TREE");
    vector<string> cylinders = Config::Instance()->getStringVectorParam("PlanningPathUpdater", "CYLINDER");
    vector<string> joints = Config::Instance()->getStringVectorParam("PlanningPathUpdater", "JOINT");
    vector<string> platforms = Config::Instance()->getStringVectorParam("PlanningPathUpdater", "PLATFORM");
    for(const auto &door: doors)m_objects.push_back(new Door(door, client_id));
    for(const auto &tree: trees)m_objects.push_back(new Tree(tree, client_id));
    for(const auto &cylinder: cylinders)m_objects.push_back(new Cylinder(cylinder, client_id));
    for(const auto &joint: joints)m_objects.push_back(new Joint(joint, client_id));
    for(const auto &platform: platforms)m_objects.push_back(new Platform(platform, client_id));
    for(const auto &object: m_objects)
    {
        cout << object->getObjectHandle() << ' ' << object->getName() << ' ' << object->getPosition() << ' ' << object->getSize() << endl;
    }
    vector<Object *> nodes;
    for(const auto &object: m_objects)
        if(object->isDoor() || object->isPlatform())
        {
            nodes.push_back(object);
        }
        auto source = Config::Instance()->getStringParam("PlanningPathUpdater", "SOURCE");
    auto destination = Config::Instance()->getStringParam("PlanningPathUpdater", "DESTINATION");
    auto grab_pos = Config::Instance()->getStringParam("PlanningPathUpdater", "GRAB_POS");
    auto n = nodes.size();
    auto s = -1, t = -1, z = -1;
    for(int i = 0; i < n; i ++)
    {
        if(nodes[i] -> getName() == source) s = i;
        if(nodes[i] -> getName() == destination) t = i;
        if(nodes[i] -> getName() == grab_pos) z = i;
    }
    // next is dynamic planning to calculate the route and task lists
    queue<pair<int, int> > q;
    float dp[n][n];
    bool v[n][n];
    pair<int,int> prev[n][n];
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
        {
            dp[i][j] = 1000000000;
            v[i][j] = false;
        }
    q.push(make_pair(s, 0));
    dp[s][0] = 0;
    while(!q.empty())
    {
        int x = q.front().first, c = q.front().second;
        for(int i = 0; i < n; i ++)
        {
            int  y = i, cc = c + (nodes[y] -> isDoor());
            MoveTask task(nodes[x], nodes[y]);
            float new_distance = dp[x][c] + task.evalTimeCost(100 * distance(nodes[x]->getPosition(), nodes[y]->getPosition()));
            if(nodes[y]->getTask() != nullptr)
            {
                new_distance += nodes[y] ->getTask()->evalTimeCost(100);
            }
            if(new_distance < dp[y][cc])
            {
                dp[y][cc] = new_distance;
                prev[y][cc] = make_pair(x, c);
                if(!v[y][cc])
                {
                    v[y][cc] = true;
                    q.push(make_pair(y, cc));
                }
            }
        }
    }
    int min_y = 3;
    for (int i = 3; i < n; i ++)
        if(dp[t][i] < dp[t][min_y])
        {
            min_y = i;
        }
    vector<int> path;
    pair<int,int> now = make_pair(t, min_y);
    while(now.first != s)
    {
        path.push_back(now.first);
        now = prev[now.first][now.second];
    }
    reverse(path.begin(), path.end());
    for(int i = 1; i < path.size(); i ++)
    {
        m_tasks.push_back(new MoveTask(nodes[path[i-1]], nodes[path[i]]));
        if (nodes[path[i]]->getTask() != nullptr)
        {
            m_tasks.push_back(nodes[path[i]]->getTask());
        }
    }
}

void PlanningPathUpdater::update()
{

}
