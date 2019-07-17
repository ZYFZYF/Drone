#ifndef DRONE_OBJECT_H
#define DRONE_OBJECT_H


#include <string>
#include "../../Common/utils/Point.h"
#include "../task/Task.h"

class Object
{
public:
    Object(const std::string &name, int client_id);

    virtual bool isDoor();

    virtual bool isJoint();

    virtual bool isTree();

    virtual bool isPlatform();

    virtual bool isCylinder();

    virtual Task *getTask();

    const std::string &getName() const;

    const Point &getPosition() const;

    const Point &getSize() const;

    simxInt getObjectHandle() const;

private:
    std::string m_name;
    int m_cid;
    Point m_pos, m_size;
    simxInt m_object_handle;
};


#endif //DRONE_OBJECT_H
