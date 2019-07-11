#include <iostream>
#include "FinishState.h"

FinishState::FinishState()
{

}

void FinishState::Enter(PathUpdater *t)
{
    std::cout << "now task finished, just keep like this and don't move" << std::endl;
}

void FinishState::Execute(PathUpdater *t)
{

}

void FinishState::Exit(PathUpdater *t)
{

}
