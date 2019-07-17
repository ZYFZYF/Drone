#ifndef DRONE_MOVETASK_H
#define DRONE_MOVETASK_H


#include "Task.h"

class MoveTask : public Task
{
public:
    explicit MoveTask(Object *source, Object *destination);

    void Enter(PlanningPathUpdater *t) override;

    void Exit(PlanningPathUpdater *t) override;

    void Execute(PlanningPathUpdater *t) override;

    const std::string getName() override;

private:
    Object *m_source_object;
    Object *m_destination_object;
};


#endif //DRONE_MOVETASK_H
