#include "basicshader.h"
#include "textures.h"
#include "QDebug"

BasicShader::BasicShader()
{
    Mm2w.normalize();
    Mw2v.normalize();
    Mv2p.normalize();
    tex1->loadImage("D:/ice.jpg");
    tex2->loadImage("D:/metal.jpg");
    tex3->loadImage("D:/floor.jpg");
    tex4->loadImage("D:/wall.jpg");
}
void BasicShader::setCam(Vector3D pos,Vector3D goal,Vector3D up,float fov,float asp,float near,float far)
{
    Mw2v.lookat(pos,goal,up);
    Mv2p.perspective(fov,asp,near,far);
}
V2F BasicShader::vertexShader(const Vertex &in){
    V2F ret;
    ret.posM2W=Mm2w*in.position;
    ret.posV2P=Mw2v*ret.posM2W;
    ret.posV2P=Mv2p*ret.posV2P;
    ret.color=in.color;
    ret.normal=in.normal;
    ret.oneDivZ=1.0/ret.posV2P.w;
    ret.texcoord = in.texcoord;
    ret.textureID=in.textureID;

    ret.texcoord*= ret.oneDivZ;
    return ret;
}
Vector4D BasicShader::fragmentShader(const V2F &in){
    Vector4D retColor;
    if(in.textureID==1)
        retColor = tex1->sample(in.texcoord);
    if(in.textureID==2)
        retColor = tex2->sample(in.texcoord);
    if(in.textureID==3)
        retColor = tex3->sample(in.texcoord);
    if(in.textureID==4)
        retColor = tex4->sample(in.texcoord);
    Vector4D n=Vector4D(in.normal.x,in.normal.y,in.normal.z,1);
    Vector4D l=lights->m_pos-in.posM2W;
    n.normalize();
    l.normalize();
    Vector4D last=Vector4D(lights->m_col.x*retColor.x,lights->m_col.y*retColor.y,lights->m_col.z*retColor.z,1);
    float tmp=n.dot(l);
    if(tmp<0)tmp=0;
    tmp=powf(tmp,0.8f);
    if(tmp>0.2f)
        retColor=last*tmp;
    else
        retColor=last*0.2f;
    tmp*=lights->intensity;
    retColor.w=1;
    return retColor;
}
