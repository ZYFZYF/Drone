#ifndef DRONE_DOOR_H
#define DRONE_DOOR_H


#include "Object.h"

class Door: public Object
{
    using Object::Object;
public:
    bool isDoor() override;
};


#endif //DRONE_DOOR_H
