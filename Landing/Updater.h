//
// Created by 97344 on 2019/7/8.
//

#ifndef LANDING_PLANNER_H
#define LANDING_PLANNER_H


class Updater
{
public:
    Updater(int time_step, int client_id);
    virtual void update() const = 0;
    void run() const;
protected:
    int m_cid;
private:
    float m_timeStep;
};


#endif //LANDING_PLANNER_H
