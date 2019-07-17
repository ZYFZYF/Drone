#ifndef DRONE_PLANNINGPATHUPDATER_H
#define DRONE_PLANNINGPATHUPDATER_H


#include <vector>
#include "PlanningUpdater.h"
#include "../../Common/config/Config.h"

class Object;
class Task;
class PlanningPathUpdater: public PlanningUpdater
{
public:
    explicit PlanningPathUpdater(int client_id);

    void update() override;

    virtual ~PlanningPathUpdater();

    void startTasks();

    void finishCurrentTask();

    void finishTasks();

    void failCurrentTask();

private:
    std::vector<Object *> m_objects;
    std::vector<Task *> m_tasks;
    int m_running_task_index;
    const simxFloat CRASH_HEIGHT = Config::Instance()->getFloatParam("PlanningPathUpdater", "CRASH_HEIGHT");
};


#endif //DRONE_PLANNINGPATHUPDATER_H
