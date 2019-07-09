//
// Created by 97344 on 2019/7/8.
//

#ifndef LANDING_PATHPLANER_H
#define LANDING_PATHPLANER_H


#include "Updater.h"

const int PATHTIMESTEP = 60;

class PathUpdater: public Updater
{
public:
    static PathUpdater * Instance(int client_id);
private:
    PathUpdater(int client_id);
    void update() const override;
};


#endif //LANDING_PATHPLANER_H
