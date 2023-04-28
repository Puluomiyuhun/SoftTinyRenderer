#ifndef VERTEX_H
#define VERTEX_H
#include"vector2d.h"
#include"vector3d.h"
#include"vector4d.h"
#include"vector"

class Vertex
{
public:
    Vector4D position;
    Vector4D color;
    Vector2D texcoord;
    Vector3D normal;
    int textureID;

    Vertex(){}
    ~Vertex(){}
    Vertex(Vector4D pos,Vector4D col,Vector2D tex,Vector3D nor,int id):
        position(pos),color(col),texcoord(tex),normal(nor),textureID(id){}
    Vertex(const Vertex &ver):
        position(ver.position),
        color(ver.color),
        texcoord(ver.texcoord),
        normal(ver.normal),
        textureID(ver.textureID){}
};
class V2F
{
public:
    Vector4D posM2W;
    Vector4D posV2P;
    Vector2D texcoord;
    Vector3D normal;
    Vector4D color;
    double oneDivZ;
    int textureID;

    V2F(){}
    V2F(Vector4D pMW, Vector4D pVP, Vector2D tex,Vector3D nor, Vector4D col, double oZ, int id):
        posM2W(pMW),posV2P(pVP),texcoord(tex),normal(nor),color(col),oneDivZ(oZ),textureID(id) {}
    V2F(const V2F& ver):
        posM2W(ver.posM2W),
        posV2P(ver.posV2P),
        texcoord(ver.texcoord),
        normal(ver.normal),
        color(ver.color),
        oneDivZ(ver.oneDivZ),
        textureID(ver.textureID)
        {}
};
class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> index;

    Mesh(){}
    ~Mesh(){}

    Mesh(const Mesh& msh):vertices(msh.vertices),index(msh.index){}
    Mesh& operator=(const Mesh& msh);
    void setVertices(Vertex* v, int count);
    void setIndex(int* i, int count);

    void triangle(Vector3D &v1,Vector3D &v2,Vector3D &v3);
    void pyramid();
    void cube(double width, double height, double depth, int id, Vector4D pos);
    void plane(double width,double height,int id,Vector4D pos);
};
#endif // VERTEX_H
