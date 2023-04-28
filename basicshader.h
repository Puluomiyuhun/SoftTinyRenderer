#ifndef BASICSHADER_H
#define BASICSHADER_H
#include "polygon.h"
#include "matrix.h"
#include "textures.h"
#include "light.h"

class BasicShader/*: public Shader*/
{
private:
    Matrix Mm2w;
    Matrix Mw2v;
    Matrix Mv2p;
    Textures *tex1=new Textures();
    Textures *tex2=new Textures();
    Textures *tex3=new Textures();
    Textures *tex4=new Textures();
public:
    Light *lights=new Light();
public:
    BasicShader();
    ~BasicShader(){}
    void setCam(Vector3D pos,Vector3D goal,Vector3D up,float fov,float asp,float near,float far);
    V2F vertexShader(const Vertex &in);
    Vector4D fragmentShader(const V2F &in);
};

#endif // BASICSHADER_H
