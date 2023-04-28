#include "renderroute.h"
#include "maincamera.h"
#include "light.h"
#include "vector4d.h"
#include <QGuiApplication>

RenderRoute::RenderRoute(int w, int h, QObject *parent)
    : QObject(parent), width(w), height(h), channel(4)
{
    stopped=false;
    pipeline=new Pipeline(width, height);
}

void RenderRoute::stopIt(){
    stopped=true;
}
void RenderRoute::loop()
{
    pipeline->initialize();
    Vector3D v1(-2,-1,0),v2(0,1,0),v3(2,-1,0),v4(0,-1,0);
    Mesh *msh1=new Mesh;
    Mesh *msh2=new Mesh;
    Mesh *msh3=new Mesh;
    Mesh *msh4=new Mesh;
    msh1->cube(2,2,2,1,Vector4D(-2,1,-2,0));
    pipeline->setIndexBuffer(msh1->index);
    pipeline->setVertexBuffer(msh1->vertices);
    msh2->cube(1,1,1,2,Vector4D(3,0.5f,-2,0));
    pipeline->setIndexBuffer(msh2->index);
    pipeline->setVertexBuffer(msh2->vertices);
    msh3->cube(3,3,3,4,Vector4D(0,1.5,2,0));
    pipeline->setIndexBuffer(msh3->index);
    pipeline->setVertexBuffer(msh3->vertices);
    msh4->plane(12,12,3,Vector4D(0,0,0,0));
    pipeline->setIndexBuffer(msh4->index);
    pipeline->setVertexBuffer(msh4->vertices);
    maincamera *camera=new maincamera;
    Light *l=new Light(Vector4D(0,3.f,0,1),Vector4D(1,1,1,1),1,1.1f);
    while(!stopped)
    {
        //pipeline->clearBuffer(Vector4D(0,0.9f,1.0f,1.0f));
        pipeline->clearBuffer(Vector4D(0,0,0,1.0f));
        pipeline->drawIndex(Pipeline::Fill,camera,l);
        pipeline->swapBuffer();
        emit frameOut(pipeline->output());
        if (QGuiApplication::keyboardModifiers() == Qt::ShiftModifier)
            camera->farAway();
        camera->rotateY(0.01f);
    }
}
