#ifndef LIGHT_H
#define LIGHT_H
#include "vector4d.h"

class Light
{
public:
    int kind;
    float intensity;
    Vector4D m_pos;
    Vector4D m_col;
public:
    Light(){}
    Light(Vector4D pos,Vector4D col,int k,float i){kind=k;intensity=i;m_col=col;m_pos=pos;}
    Light(Light *l){kind=l->kind;intensity=l->intensity;m_col=l->m_col;m_pos=l->m_pos;}
    ~Light(){}
};

#endif // LIGHT_H
