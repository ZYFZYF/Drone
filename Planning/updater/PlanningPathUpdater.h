#ifndef DRONE_PLANNINGPATHUPDATER_H
#define DRONE_PLANNINGPATHUPDATER_H


#include <vector>
#include "PlanningUpdater.h"
#include "../object/Object.h"

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
