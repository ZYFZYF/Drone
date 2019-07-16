#ifndef DRONE_OBJECT_H
#define DRONE_OBJECT_H


#include <string>
#include "../utils/Point.h"

class Object
{
public:
    Object(const std::string &name, int client_id);

    virtual bool isDoor();

    virtual bool isJoint();

    virtual bool isTree();

    virtual bool isPlatform();

    virtual bool isCylinder();

private:
    std::string m_name;
    int m_cid;
    Point m_pos, m_size;
    simxInt m_object_handle;
};


#endif //DRONE_OBJECT_H
