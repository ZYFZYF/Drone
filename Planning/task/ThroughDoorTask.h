#ifndef DRONE_THROUGHDOORTASK_H
#define DRONE_THROUGHDOORTASK_H


#include "Task.h"
#include "../object/Object.h"

class ThroughDoorTask: public Task
{
public:
    explicit ThroughDoorTask(Object *object);

    void Execute(PlanningPathUpdater *t) override;

    const std::string getName() override;

    void Enter(PlanningPathUpdater *t) override;

    void Exit(PlanningPathUpdater *t) override;
private:
    Object *m_object;
};


#endif //DRONE_THROUGHDOORTASK_H
