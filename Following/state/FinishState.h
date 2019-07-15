#ifndef LANDING_FINISHSTATE_H
#define LANDING_FINISHSTATE_H


#include <PathUpdater.h>

class FinishState: public State<PathUpdater>
{
public:
    FinishState();

    void Enter(PathUpdater *t) override;

    void Execute(PathUpdater *t) override;

    void Exit(PathUpdater *t) override;
};


#endif //LANDING_FINISHSTATE_H
