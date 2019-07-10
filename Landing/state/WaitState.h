#ifndef LANDING_WAITSTATE_H
#define LANDING_WAITSTATE_H


#include <PathUpdater.h>

class WaitState : public State<PathUpdater>
{
public:


    void Enter(PathUpdater *t) override;

    void Execute(PathUpdater *t) override;

    void Exit(PathUpdater *t) override;

    static WaitState *Instance(int remain_rounds, State *next_state);

    void reset(int remain_rounds, State *next_state);

private:
    WaitState();
    int m_remain_rounds;
    State *m_next_state;
};


#endif //LANDING_WAITSTATE_H
