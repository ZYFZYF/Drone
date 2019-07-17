#ifndef DRONE_DOOR_H
#define DRONE_DOOR_H


#include "Object.h"

class Door: public Object
{
public:
    Door(const std::string &name, int client_id);

    bool isDoor() override;
};


#endif //DRONE_DOOR_H
