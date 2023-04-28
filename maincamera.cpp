#include "maincamera.h"
#include "vector4d.h"
#include "matrix.h"
#include "stdio.h"

maincamera::maincamera()
{
    //pos=Vector3D(0,8,-18);
    pos=Vector3D(0,12,-24);
    goal=Vector3D(0,0,0);
    up=Vector3D(0,1,0);
    fov=45*3.14/180.f;
    asp=1280/767.f;
    near=1.f;
    far=50.f;
}
maincamera::maincamera(Vector3D mpos, Vector3D mgoal, Vector3D mup, float mfov, float masp, float mnear, float mfar)
{
    pos=mpos;
    goal=mgoal;
    up=mup;
    fov=mfov;
    asp=masp;
    near=mnear;
    far=mfar;
}

void maincamera::rotateY(float angle)
{
    Vector4D pos4(pos.x,pos.y,pos.z,1);
    Matrix rot;
    rot.normalize();
    rot.rotationY(angle);
    pos4=rot*pos4;
    pos.setX(pos4.x);
    pos.setY(pos4.y);
    pos.setZ(pos4.z);
}

void maincamera::farAway()
{
    pos-=Vector3D(0,0,0.1f);
}
