#ifndef DRONE_GRABTASK_H
#define DRONE_GRABTASK_H


#include "Task.h"
#include "../object/Object.h"

class GrabTask: public Task
{
public:
    //not a good implement, lead to shared ptr

    explicit GrabTask(Object *object);

    void Enter(PlanningPathUpdater *t) override;

    void Exit(PlanningPathUpdater *t) override;

    void Execute(PlanningPathUpdater *t) override;

    const std::string getName() override;

private:
    Object *m_object;
};


#endif //DRONE_GRABTASK_H
