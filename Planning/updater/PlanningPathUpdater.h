#ifndef DRONE_PLANNINGPATHUPDATER_H
#define DRONE_PLANNINGPATHUPDATER_H


#include <vector>
#include "PlanningUpdater.h"

class Object;
class Task;
class PlanningPathUpdater: public PlanningUpdater
{
public:
    explicit PlanningPathUpdater(int client_id);

    void update() override;

private:
    std::vector<Object *> m_objects;
    std::vector<Task *> m_tasks;
};


#endif //DRONE_PLANNINGPATHUPDATER_H
