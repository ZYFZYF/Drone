#ifndef DRONE_PLATFORM_H
#define DRONE_PLATFORM_H


#include "Object.h"

class Platform : public Object
{
    using Object::Object;
public:
    bool isPlatform() override;
};


#endif //DRONE_PLATFORM_H
