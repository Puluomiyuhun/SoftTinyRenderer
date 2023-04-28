#ifndef SHADER_H
#define SHADER_H
#include "polygon.h"

class Shader
{
public:
    Shader(){}
    virtual ~Shader(){}
    virtual void setCam(Vector3D pos,Vector3D goal,Vector3D up,float fov,float asp,float near,float far)=0;
    virtual V2F vertexShader(const Vertex &in)=0;
    virtual Vector4D fragmentShader(const V2F &in)=0;
};

#endif // SHADER_H
