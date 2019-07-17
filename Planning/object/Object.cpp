#include <iostream>
#include "Object.h"
#include "../../Common/utils/utils.h"

Object::Object(const std::string &name, int client_id) : m_name(name), m_cid(client_id)
{
    simxGetObjectHandle(m_cid, m_name.c_str(), &m_object_handle, simx_opmode_blocking);
    m_pos = utils::getObjectPosition(m_object_handle, m_cid);
    //a little naive but who care _(:з」∠)_
    simxFloat min_x, min_y, min_z, max_x, max_y, max_z;
    simxGetObjectFloatParameter(m_cid, m_object_handle, sim_objfloatparam_modelbbox_min_x, &min_x,
                                simx_opmode_blocking);
    simxGetObjectFloatParameter(m_cid, m_object_handle, sim_objfloatparam_modelbbox_min_y, &min_y,
                                simx_opmode_blocking);
    simxGetObjectFloatParameter(m_cid, m_object_handle, sim_objfloatparam_modelbbox_min_z, &min_z,
                                simx_opmode_blocking);
    simxGetObjectFloatParameter(m_cid, m_object_handle, sim_objfloatparam_modelbbox_max_x, &max_x,
                                simx_opmode_blocking);
    simxGetObjectFloatParameter(m_cid, m_object_handle, sim_objfloatparam_modelbbox_max_y, &max_y,
                                simx_opmode_blocking);
    simxGetObjectFloatParameter(m_cid, m_object_handle, sim_objfloatparam_modelbbox_max_z, &max_z,
                                simx_opmode_blocking);
    m_size = Point(fabsf(max_x - min_x), fabsf(max_y - min_y), fabsf(max_z - min_z));
}

bool Object::isDoor()
{
    return false;
}

bool Object::isJoint()
{
    return false;
}

bool Object::isTree()
{
    return false;
}

bool Object::isPlatform()
{
    return false;
}

bool Object::isCylinder()
{
    return false;
}

const std::string &Object::getName() const
{
    return m_name;
}

const Point &Object::getPosition() const
{
    return m_pos;
}

const Point &Object::getSize() const
{
    return m_size;
}

simxInt Object::getObjectHandle() const
{
    return m_object_handle;
}

Task *Object::getTask()
{
    return nullptr;
}
