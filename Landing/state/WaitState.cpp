//
// Created by 97344 on 2019/7/10.
//

#include <iostream>
#include "WaitState.h"

void WaitState::Enter(PathUpdater *t)
{
    std::cout << "wait to keep stable for " << m_remain_rounds << " rounds" << std::endl;
}

void WaitState::Execute(PathUpdater *t)
{
    m_remain_rounds --;
    std::cout << "remain " << m_remain_rounds << " rounds" << std::endl;
    if(!m_remain_rounds)
    {
        t->changeState(m_next_state);
    }
}

void WaitState::Exit(PathUpdater *t)
{
    std::cout << "time up, move to next state" << std::endl;
}

WaitState::WaitState():m_remain_rounds(1), m_next_state(nullptr)
{

}

WaitState *WaitState::Instance(int remain_rounds, State *next_state)
{
    static WaitState instance;
    instance.reset(remain_rounds, next_state);
    return &instance;
}

void WaitState::reset(int remain_rounds, State *next_state)
{
    m_remain_rounds = remain_rounds;
    m_next_state = next_state;
}
