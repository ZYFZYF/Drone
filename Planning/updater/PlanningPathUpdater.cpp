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
#include "../task/Task.h"
#include "../route/NaiveRouter.h"
#include "../object/Entrance.h"


using namespace std;
queue<pair<int, int> > q;
const int NODES_NUM = 18;
float dp[NODES_NUM][1 << NODES_NUM];
bool v[NODES_NUM][1 << NODES_NUM];
pair<int, int> prevNode[NODES_NUM][1 << NODES_NUM];

PlanningPathUpdater::PlanningPathUpdater(int client_id) : PlanningUpdater(
        Config::Instance()->getIntParam("PlanningPathUpdater", "TIME_STEP"), client_id), crash_rounds(0)
{
    //can't get the first object's info
    Object trash("nothing", client_id);
    vector<string> doors = Config::Instance()->getStringVectorParam("PlanningPathUpdater", "DOOR");
    vector<string> trees = Config::Instance()->getStringVectorParam("PlanningPathUpdater", "TREE");
    vector<string> cylinders = Config::Instance()->getStringVectorParam("PlanningPathUpdater", "CYLINDER");
    vector<string> joints = Config::Instance()->getStringVectorParam("PlanningPathUpdater", "JOINT");
    vector<string> platforms = Config::Instance()->getStringVectorParam("PlanningPathUpdater", "PLATFORM");
    for (const auto &door: doors)m_objects.push_back(new Door(door, client_id));
    for (const auto &tree: trees)m_objects.push_back(new Tree(tree, client_id));
    for (const auto &cylinder: cylinders)m_objects.push_back(new Cylinder(cylinder, client_id));
    for (const auto &joint: joints)m_objects.push_back(new Joint(joint, client_id));
    for (const auto &platform: platforms)m_objects.push_back(new Platform(platform, client_id));
    for (const auto &object: m_objects)
    {
        cout << object->getObjectHandle() << ' ' << object->getName() << ' ' << object->getPosition() << ' '
             << object->getSize() << endl;
    }
    //add router
    if (ROUTE_ALGORITHM == "NAIVE")
    {
        m_router = new NaiveRouter();
    }
    for (const auto &object: m_objects)
    {
        m_router->addObstacle(Obstacle(object));
    }
    //construct
    vector<Object *> nodes;
    for (const auto &object: m_objects)
    {
        if (object->isPlatform())
        {
            nodes.push_back(object);
        }
        if (object->isDoor())
        {
            nodes.push_back(dynamic_cast<Door *>(object)->getFrontEntrance());
            nodes.push_back(dynamic_cast<Door *>(object)->getBackEntrance());
        }
    }
    auto source = Config::Instance()->getStringParam("PlanningPathUpdater", "SOURCE");
    auto destination = Config::Instance()->getStringParam("PlanningPathUpdater", "DESTINATION");
    auto grab_pos = Config::Instance()->getStringParam("PlanningPathUpdater", "GRAB_POS");
    auto n = nodes.size();
    auto m = 1 << n;
    auto s = -1, t = -1, z = -1;
    for (int i = 0; i < n; i++)
    {
        if (nodes[i]->getName() == source) s = i;
        if (nodes[i]->getName() == destination) t = i;
        if (nodes[i]->getName() == grab_pos) z = i;
        cout << i << ' ' << nodes[i]->getName() << endl;
    }
    // next is dynamic planning to calculate the route and task lists
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            dp[i][j] = 1000000000;
            v[i][j] = false;
        }
    q.push(make_pair(s, 1 << s));
    dp[s][1 << s] = 0;
    while (!q.empty())
    {
        auto x = q.front().first, c = q.front().second;
        q.pop();
        for (int i = 0; i < n; i++)
            if (!(c >> i & 1))
            {
                int y = i, cc = c + (1 << i), yy=y;
                if (nodes[y]->isEntrance())
                {
                    Object *next_entrance = dynamic_cast<Entrance *>(nodes[y])->getOtherEntrance();
                    for (int i = 0; i < n; i++)
                    {
                        if (nodes[i] == next_entrance)
                        {
                            yy = i;
                            break;
                        }
                    }
                    if (cc >> yy & 1)continue;
                    cc += 1 << yy;
                }
                MoveTask task(nodes[x], nodes[y]);
                float new_distance = dp[x][c] + task.getDistance(m_router);
                if (nodes[y]->getTask() != nullptr)
                {
                    new_distance += nodes[y]->getTask()->evalTimeCost(1000000);
                }
                if (new_distance < dp[yy][cc])
                {
                    dp[yy][cc] = new_distance;
                    prevNode[yy][cc] = make_pair(x, c);
                    if (!v[yy][cc])
                    {
                        v[yy][cc] = true;
                        q.push(make_pair(yy, cc));
                    }
                }
            }
    }
    auto min_y = m - 1;
    for (auto i = 0; i < m; i++)
    {
        //条件改为通过3个门口,前面的3个门可以推出来
        auto cnt = 0;
        for (auto j = 0; j < n; j++)
            if ((i >> j & 1) && nodes[j]->isEntrance())
                cnt++;
        if (cnt < 3 || !(i >> z & 1)) continue;

        if (dp[t][i] < dp[t][min_y])
        {
            min_y = i;
        }
    }

    vector<int> path;
    pair<int, int> now = make_pair(t, min_y);
    while (true)
    {
        path.push_back(now.first);
        if (now.first == s)break;
        now = prevNode[now.first][now.second];
        cout << now.first << ' ' << now.second << ' ' << dp[now.first][now.second] << endl;
    }
    reverse(path.begin(), path.end());
    for (auto i: path)
    {
        cout << i << ' ' << nodes[i]->getName() << endl;
    }
    for (int i = 1; i < path.size(); i++)
    {
        if (nodes[path[i]]->isEntrance())
        {
            m_tasks.push_back(new MoveTask(nodes[path[i - 1]], dynamic_cast<Entrance *>(nodes[path[i]])->getOtherEntrance()));
            m_tasks.push_back(dynamic_cast<Entrance *>(nodes[path[i]])->getParent()->getTask());
        } else
        {
            m_tasks.push_back(new MoveTask(nodes[path[i - 1]], nodes[path[i]]));
            if (nodes[path[i]]->getTask() != nullptr)
            {
                m_tasks.push_back(nodes[path[i]]->getTask());
            }
        }
    }
    for (const auto &task: m_tasks)
    {
        cout << task->getName() << endl;
    }
    //start the first task
    startTasks();
}

void PlanningPathUpdater::update()
{
    if (m_running_task_index >= 0 && m_running_task_index < m_tasks.size())
    {
        //如果已经坠机了就结束吧，这几个函数的调用关系有点臭
        if (getDronePosition()[2] < CRASH_HEIGHT)
        {
            crash_rounds++;
        } else
        {
            crash_rounds = 0;
        }
        if (crash_rounds >= CRASH_ROUNDS_THRESHOLD)
        {
            failCurrentTask();
        } else
        {
            m_tasks[m_running_task_index]->Execute(this);
        }
    } else
    {
        cout << "已经不用再努力了_(:з」∠)_" << endl;
    }
}

PlanningPathUpdater::~PlanningPathUpdater()
{
    //point in vector need to release alone
    //tasks first
    for (auto &m_task : m_tasks)
    {
        if (m_task != nullptr)
        {
            delete m_task;
            m_task = nullptr;
        }
    }
    for (auto &m_object : m_objects)
    {
        if (m_object != nullptr)
        {
            delete m_object;
            m_object = nullptr;
        }
    }
    delete m_router;
}

void PlanningPathUpdater::startTasks()
{
    m_running_task_index = 0;
    m_tasks[m_running_task_index]->Enter(this);
}

void PlanningPathUpdater::finishCurrentTask()
{
    m_tasks[m_running_task_index]->Exit(this);
    m_running_task_index++;
    if (m_running_task_index == m_tasks.size())
    {
        finishTasks();
        return;
    }
    m_tasks[m_running_task_index]->Enter(this);
}

void PlanningPathUpdater::finishTasks()
{
    cout << "Finish all tasks. Congratulations to you!!!!!!!!!" << endl;
    setFinished();
}

void PlanningPathUpdater::failCurrentTask()
{
    m_tasks[m_running_task_index]->Fail();
    m_running_task_index = -1;
    cout << "失败了,已经不用再努力了" << endl;
    setFinished();
}

std::vector<Point> PlanningPathUpdater::getPathPoints(const Point &start_pos, const Point &end_pos)
{
    return m_router->route(start_pos, end_pos);
}
