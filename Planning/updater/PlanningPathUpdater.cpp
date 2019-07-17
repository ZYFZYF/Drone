#include <iostream>
#include "PlanningPathUpdater.h"
#include "../../Common/config/Config.h"
#include "../../Common/object/Object.h"
#include "../../Common/object/Door.h"
#include "../../Common/object/Tree.h"
#include "../../Common/object/Cylinder.h"
#include "../../Common/object/Joint.h"
#include "../../Common/object/Platform.h"

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
}

void PlanningPathUpdater::update()
{

}
