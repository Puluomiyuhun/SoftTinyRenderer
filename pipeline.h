#ifndef PIPELINE_H
#define PIPELINE_H
#include "basicshader.h"
#include "framebuffer.h"
#include "matrix.h"
#include "maincamera.h"
#include "light.h"

class Pipeline
{
private:
    int width, height;
    BasicShader *m_shader;
    FrameBuffer *m_frontBuffer;
    FrameBuffer *m_backBuffer;
    FrameBuffer *m_tmp;
    Matrix viewPortMatrix;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
public:
    enum ShadingMode{Simple,Gouraud,Phong};
    enum RenderMode{Wire,Fill};
public:
    Pipeline(int w,int h)
        :width(w),height(h)
        ,m_shader(nullptr),m_frontBuffer(nullptr)
        ,m_backBuffer(nullptr),m_tmp(nullptr){}
    ~Pipeline();

    void initialize();
    void clearBuffer(const Vector4D &color, bool depth = false);
    void setVertexBuffer(const std::vector<Vertex> &vertices){
        m_vertices.insert(m_vertices.end(),vertices.begin(),vertices.end());
    }
    void setIndexBuffer(std::vector<unsigned int> &indices){
        for(int i=0;i<indices.size();i++)indices[i]+=m_vertices.size();
        m_indices.insert(m_indices.end(),indices.begin(),indices.end());
    }
    void setShaderMode(ShadingMode mode);
    void drawIndex(RenderMode mode,maincamera *camera,Light *l);
    void swapBuffer();
    unsigned char *output(){return m_frontBuffer->getColorBuffer();}

    V2F lerp(const V2F &n1, const V2F &n2, float weight);
    void bresenham(const V2F &from, const V2F &to);
    int getColor(int x,int y,int c);
    void scanLinePerRow(const V2F &left, const V2F &right);
    void rasterTopTriangle(V2F &v1, V2F &v2, V2F &v3);
    void rasterBottomTriangle(V2F &v1, V2F &v2, V2F &v3);
    void edgeWalkingFillRasterization(const V2F &v1, const V2F &v2, const V2F &v3);
};

#endif // PIPELINE_H
