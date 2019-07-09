//
// Created by 97344 on 2019/7/8.
//

#include <iostream>
#include "PathUpdater.h"
PathUpdater* PathUpdater::Instance(int client_id)
{
    static PathUpdater instance(client_id);
    return &instance;
}
PathUpdater::PathUpdater(int client_id): Updater(PATHTIMESTEP, client_id)
{
    std::cout<<"PathPlanner constrcuted"<<std::endl;
}
void PathUpdater::update() const
{
    std::cout<<"I'm Path"<<std::endl;
}