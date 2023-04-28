#ifndef MAINCAMERA_H
#define MAINCAMERA_H
#include"vector3d.h"

class maincamera
{
public:
    Vector3D pos,goal,up;
    float fov,asp,near,far;
public:
    maincamera();
    maincamera(Vector3D mpos,Vector3D mgoal,Vector3D mup,float mfov,float masp,float mnear,float mfar);
    void rotateY(float angle);
    void farAway();
};

#endif // MAINCAMERA_H
