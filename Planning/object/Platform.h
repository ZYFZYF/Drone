#ifndef DRONE_PLATFORM_H
#define DRONE_PLATFORM_H


#include "Object.h"

class Platform : public Object
{
public:
    Platform(const std::string &name, int client_id);

    bool isPlatform() override;
};


#endif //DRONE_PLATFORM_H
