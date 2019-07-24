#ifndef DRONE_OBJECT_H
#define DRONE_OBJECT_H


#include <string>
#include "../../Common/utils/Point.h"
#include "../task/Task.h"

class Object
{
public:
    Object();

    Object(const std::string &name, int client_id);

    virtual bool isDoor();

    virtual bool isJoint();

    virtual bool isTree();

    virtual bool isPlatform();

    virtual bool isCylinder();

    virtual bool isEntrance();

    Task *getTask();

    virtual const std::string &getName() const;

    const Point &getPosition() const;

    virtual const Point getValidPosition() const;

    const Point &getSize() const;

    simxInt getObjectHandle() const;

protected:
    Task * m_task;
    Point m_pos, m_size;
    std::string m_name;
private:
    int m_cid;
    simxInt m_object_handle;
};


#endif //DRONE_OBJECT_H
