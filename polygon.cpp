#include "polygon.h"

Mesh& Mesh::operator=(const Mesh& msh)
{
    vertices=msh.vertices;
    index=msh.index;
    return *this;
}

void Mesh::setVertices(Vertex* v, int count)
{
    vertices.resize(static_cast<unsigned long>(count));
    new(&vertices[0])std::vector<Vertex>(v,v+count);
}

void Mesh::setIndex(int* i, int count)
{
    index.resize(static_cast<unsigned long>(count));
    new(&index)std::vector<unsigned int>(i,i+count);
}

void Mesh::triangle(Vector3D &v1, Vector3D &v2, Vector3D &v3)
{
    vertices.resize(3);
    index.resize(3);
    vertices[0].position=v1;
    vertices[0].normal=Vector3D(0.f,0.f,1.f);
    vertices[0].color=Vector4D(1.f,0.f,0.f,1.f);
    vertices[0].texcoord=Vector2D(0.f,0.f);
    vertices[1].position=v2;
    vertices[1].normal=Vector3D(0.f,0.f,1.f);
    vertices[1].color=Vector4D(0.f,1.f,0.f,1.f);
    vertices[1].texcoord=Vector2D(1.f,0.f);
    vertices[2].position=v3;
    vertices[2].normal=Vector3D(0.f,0.f,1.f);
    vertices[2].color=Vector4D(0.f,0.f,1.f,1.f);
    vertices[2].texcoord=Vector2D(0.5f,1.f);
    index[0]=0;
    index[1]=1;
    index[2]=2;
}

void Mesh::pyramid()
{
    vertices.resize(6);
    index.resize(6);
    vertices[0].position=Vector3D(-1.732f,0,-1);
    vertices[0].normal=Vector3D(0.f,0.f,1.f);
    vertices[0].color=Vector4D(1.f,0.f,0.f,1.f);
    vertices[0].texcoord=Vector2D(0.f,0.f);
    vertices[1].position=Vector3D(0,0,2.f);
    vertices[1].normal=Vector3D(0.f,0.f,1.f);
    vertices[1].color=Vector4D(0.f,1.f,0.f,1.f);
    vertices[1].texcoord=Vector2D(1.f,0.f);
    vertices[2].position=Vector3D(1.732f,0,-1);
    vertices[2].normal=Vector3D(0.f,0.f,1.f);
    vertices[2].color=Vector4D(0.f,0.f,1.f,1.f);
    vertices[2].texcoord=Vector2D(0.5f,1.f);
    vertices[3].position=Vector3D(0,2,0);
    vertices[3].normal=Vector3D(0.f,0.f,1.f);
    vertices[3].color=Vector4D(1.f,1.f,1.f,1.f);
    vertices[3].texcoord=Vector2D(0.5f,1.f);
    index[0]=0;
    index[1]=1;
    index[2]=2;
    index[3]=3;
    index[4]=0;
    index[5]=1;
}

void Mesh::cube(double width, double height, double depth, int id, Vector4D pos)
{
    vertices.resize(24);
    index.resize(36);

    float halfW = width * 0.5f;
    float halfH = height * 0.5f;
    float halfD = depth * 0.5f;
    //front
    vertices[0].position = Vector3D(halfW, halfH, halfD);
    vertices[0].normal = Vector3D(0.f, 0.f, 1.f);
    vertices[0].color = Vector4D(1.f, 0.f, 0.f, 1.f);
    vertices[0].texcoord = Vector2D(1.f, 1.f);
    vertices[1].position = Vector3D(-halfW, halfH, halfD);
    vertices[1].normal = Vector3D(0.f, 0.f, 1.f);
    vertices[1].color = Vector4D(0.f, 1.f, 0.f, 1.f);
    vertices[1].texcoord = Vector2D(0.f, 1.f);
    vertices[2].position = Vector3D(-halfW,-halfH, halfD);
    vertices[2].normal = Vector3D(0.f, 0.f, 1.f);
    vertices[2].color = Vector4D(0.f, 0.f, 1.f, 1.f);
    vertices[2].texcoord = Vector2D(0.f, 0.f);
    vertices[3].position = Vector3D(halfW, -halfH, halfD);
    vertices[3].normal = Vector3D(0.f, 0.f, 1.f);
    vertices[3].color = Vector4D(0.f, 1.f, 1.f, 1.f);
    vertices[3].texcoord = Vector2D(1.f, 0.f);
    //left
    vertices[4].position = Vector3D(-halfW, +halfH, halfD);
    vertices[4].normal = Vector3D(-1.f, 0.f, 0.f);
    vertices[4].color = Vector4D(0.f, 0.f, 1.f, 1.f);
    vertices[4].texcoord = Vector2D(1.f, 1.f);
    vertices[5].position = Vector3D(-halfW, +halfH, -halfD);
    vertices[5].normal = Vector3D(-1.f, 0.f, 0.f);
    vertices[5].color = Vector4D(1.f, 1.f, 0.f, 1.f);
    vertices[5].texcoord = Vector2D(0.f, 1.f);
    vertices[6].position = Vector3D(-halfW, -halfH, -halfD);
    vertices[6].normal = Vector3D(-1.f, 0.f, 0.f);
    vertices[6].color = Vector4D(0.f, 1.f, 0.f, 1.f);
    vertices[6].texcoord = Vector2D(0.f, 0.f);
    vertices[7].position = Vector3D(-halfW, -halfH, halfD);
    vertices[7].normal = Vector3D(-1.f, 0.f, 0.f);
    vertices[7].color = Vector4D(1.f, 1.f, 1.f, 1.f);
    vertices[7].texcoord = Vector2D(1.f, 0.f);
    //back
    vertices[8].position = Vector3D(-halfW, +halfH, -halfD);
    vertices[8].normal = Vector3D(0.f, 0.f, -1.f);
    vertices[8].color = Vector4D(1.f, 0.f, 1.f, 1.f);
    vertices[8].texcoord = Vector2D(0.f, 0.f);
    vertices[9].position = Vector3D(+halfW, +halfH, -halfD);
    vertices[9].normal = Vector3D(0.f, 0.f, -1.f);
    vertices[9].color = Vector4D(0.f, 1.f, 1.f, 1.f);
    vertices[9].texcoord = Vector2D(1.f, 0.f);
    vertices[10].position = Vector3D(+halfW, -halfH, -halfD);
    vertices[10].normal = Vector3D(0.f, 0.f, -1.f);
    vertices[10].color = Vector4D(1.f, 1.f, 0.f, 1.f);
    vertices[10].texcoord = Vector2D(1.f, 1.f);
    vertices[11].position = Vector3D(-halfW, -halfH, -halfD);
    vertices[11].normal = Vector3D(0.f, 0.f, -1.f);
    vertices[11].color = Vector4D(0.f, 0.f, 1.f, 1.f);
    vertices[11].texcoord = Vector2D(0.f, 1.f);
    //right
    vertices[12].position = Vector3D(halfW, +halfH, -halfD);
    vertices[12].normal = Vector3D(1.f, 0.f, 0.f);
    vertices[12].color = Vector4D(0.f, 1.f, 0.f, 1.f);
    vertices[12].texcoord = Vector2D(0.f, 0.f);
    vertices[13].position = Vector3D(halfW, +halfH, +halfD);
    vertices[13].normal = Vector3D(1.f, 0.f, 0.f);
    vertices[13].color = Vector4D(1.f, 0.f, 0.f, 1.f);
    vertices[13].texcoord = Vector2D(1.f, 0.f);
    vertices[14].position = Vector3D(halfW, -halfH, +halfD);
    vertices[14].normal = Vector3D(1.f, 0.f, 0.f);
    vertices[14].color = Vector4D(0.f, 1.f, 1.f, 1.f);
    vertices[14].texcoord = Vector2D(1.f, 1.f);
    vertices[15].position = Vector3D(halfW, -halfH, -halfD);
    vertices[15].normal = Vector3D(1.f, 0.f, 0.f);
    vertices[15].color = Vector4D(1.f, 0.f, 1.f, 1.f);
    vertices[15].texcoord = Vector2D(0.f, 1.f);
    //top
    vertices[16].position = Vector3D(+halfW, halfH, -halfD);
    vertices[16].normal = Vector3D(0.f, 1.f, 0.f);
    vertices[16].color = Vector4D(0.f, 0.f, 0.f, 1.f);
    vertices[16].texcoord = Vector2D(0.f, 0.f);
    vertices[17].position = Vector3D(-halfW, halfH, -halfD);
    vertices[17].normal = Vector3D(0.f, 1.f, 0.f);
    vertices[17].color = Vector4D(1.f, 1.f, 0.f, 1.f);
    vertices[17].texcoord = Vector2D(1.f, 0.f);
    vertices[18].position = Vector3D(-halfW, halfH, halfD);
    vertices[18].normal = Vector3D(0.f, 1.f, 0.f);
    vertices[18].color = Vector4D(0.f, 1.f, 1.f, 1.f);
    vertices[18].texcoord = Vector2D(1.f, 1.f);
    vertices[19].position = Vector3D(+halfW, halfH, halfD);
    vertices[19].normal = Vector3D(0.f, 1.f, 0.f);
    vertices[19].color = Vector4D(1.f, 0.f, 0.f, 1.f);
    vertices[19].texcoord = Vector2D(0.f, 1.f);
    //down
    vertices[20].position = Vector3D(+halfW, -halfH, -halfD);
    vertices[20].normal = Vector3D(0.f, -1.f, 0.f);
    vertices[20].color = Vector4D(0.f, 0.f, 1.f, 1.f);
    vertices[20].texcoord = Vector2D(0.f, 0.f);
    vertices[21].position = Vector3D(+halfW, -halfH, +halfD);
    vertices[21].normal = Vector3D(0.f, -1.f, 0.f);
    vertices[21].color = Vector4D(1.f, 1.f, 1.f, 1.f);
    vertices[21].texcoord = Vector2D(1.f, 0.f);
    vertices[22].position = Vector3D(-halfW, -halfH, +halfD);
    vertices[22].normal = Vector3D(0.f, -1.f, 0.f);
    vertices[22].color = Vector4D(0.f, 1.f, 0.f, 1.f);
    vertices[22].texcoord = Vector2D(1.f, 1.f);
    vertices[23].position = Vector3D(-halfW, -halfH, -halfD);
    vertices[23].normal = Vector3D(0.f, -1.f, 0.f);
    vertices[23].color = Vector4D(1.f, 0.f, 1.f, 1.f);
    vertices[23].texcoord = Vector2D(0.f, 1.f);

    for(int i=0;i<24;i++)
    {
        vertices[i].textureID=id;
        vertices[i].position+=pos;
        //vertices[i].color=Vector4D(0,0,0,0);
    }

    //front
    index[0] = 0;
    index[1] = 1;
    index[2] = 2;
    index[3] = 0;
    index[4] = 2;
    index[5] = 3;
    //left
    index[6] = 4;
    index[7] = 5;
    index[8] = 6;
    index[9] = 4;
    index[10] = 6;
    index[11] = 7;
    //back
    index[12] = 8;
    index[13] = 9;
    index[14] = 10;
    index[15] = 8;
    index[16] = 10;
    index[17] = 11;
    //right
    index[18] = 12;
    index[19] = 13;
    index[20] = 14;
    index[21] = 12;
    index[22] = 14;
    index[23] = 15;
    //top
    index[24] = 16;
    index[25] = 17;
    index[26] = 18;
    index[27] = 16;
    index[28] = 18;
    index[29] = 19;
    //down
    index[30] = 20;
    index[31] = 21;
    index[32] = 22;
    index[33] = 20;
    index[34] = 22;
    index[35] = 23;
}

void Mesh::plane(double width,double height,int id,Vector4D pos)
{
    vertices.resize(4);
    index.resize(6);
    vertices[0].position = Vector3D(-width/2, 0, -height/2);
    vertices[0].normal = Vector3D(0.f, 1.f, 0.f);
    vertices[0].color = Vector4D(1.f, 0.f, 0.f, 1.f);
    vertices[0].texcoord = Vector2D(0.f, 0.f);
    vertices[1].position = Vector3D(width/2, 0, -height/2);
    vertices[1].normal = Vector3D(0.f, 1.f, 0.f);
    vertices[1].color = Vector4D(1.f, 0.f, 0.f, 1.f);
    vertices[1].texcoord = Vector2D(1.f, 0.f);
    vertices[2].position = Vector3D(-width/2, 0, height/2);
    vertices[2].normal = Vector3D(0.f, 1.f, 0.f);
    vertices[2].color = Vector4D(1.f, 0.f, 0.f, 1.f);
    vertices[2].texcoord = Vector2D(0.f, 1.f);
    vertices[3].position = Vector3D(width/2, 0, height/2);
    vertices[3].normal = Vector3D(0.f, 1.f, 0.f);
    vertices[3].color = Vector4D(1.f, 0.f, 0.f, 1.f);
    vertices[3].texcoord = Vector2D(1.f, 1.f);

    for(int i=0;i<4;i++)
    {
        vertices[i].textureID=id;
        vertices[i].position+=pos;
    }

    index[0]=0;
    index[1]=1;
    index[2]=2;
    index[3]=1;
    index[4]=2;
    index[5]=3;
}
