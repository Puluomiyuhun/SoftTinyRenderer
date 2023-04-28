#include "pipeline.h"
#include "basicshader.h"
#include "algorithm"
using namespace std;

Pipeline::~Pipeline()
{
    if(m_shader)delete m_shader;
    if(m_frontBuffer)delete m_frontBuffer;
    if(m_backBuffer)delete m_backBuffer;
    m_shader=nullptr;
    m_frontBuffer=nullptr;
    m_backBuffer=nullptr;
    m_tmp=nullptr;
}

void Pipeline::initialize()
{
    if(m_frontBuffer!=nullptr)delete m_frontBuffer;
    if(m_backBuffer)delete m_backBuffer;
    if(m_shader)delete m_shader;
    viewPortMatrix.viewPort(0,0,width,height);
    m_frontBuffer=new FrameBuffer(width,height);
    m_backBuffer=new FrameBuffer(width,height);
    m_tmp=new FrameBuffer(width,height);
    m_shader=new BasicShader();
    m_tmp->Fill(Vector4D(0,0,0,1));
}

void Pipeline::drawIndex(RenderMode mode,maincamera *camera,Light *l)
{
    if(m_indices.empty())return;
    m_shader->setCam(camera->pos,camera->goal,camera->up,camera->fov,camera->asp,camera->near,camera->far);
    m_shader->lights=new Light(l);
    for(unsigned int i=0;i<m_indices.size()/3;i++)
    {
        Vertex vv1=m_vertices[m_indices[i*3]],vv2=m_vertices[m_indices[i*3+1]],vv3=m_vertices[m_indices[i*3+2]];
        V2F v1=m_shader->vertexShader(vv1),v2=m_shader->vertexShader(vv2),v3=m_shader->vertexShader(vv3);
        v1.posV2P/=v1.posV2P.w;
        v2.posV2P/=v2.posV2P.w;
        v3.posV2P/=v3.posV2P.w;
        v1.posV2P=viewPortMatrix*v1.posV2P;
        v2.posV2P=viewPortMatrix*v2.posV2P;
        v3.posV2P=viewPortMatrix*v3.posV2P;
        m_backBuffer->Cover(static_cast<int>(v1.posV2P.x),static_cast<int>(v1.posV2P.y),v1.color);
        m_backBuffer->Cover(static_cast<int>(v2.posV2P.x),static_cast<int>(v2.posV2P.y),v2.color);
        m_backBuffer->Cover(static_cast<int>(v3.posV2P.x),static_cast<int>(v3.posV2P.y),v3.color);
        if(mode==Wire)
        {
            bresenham(v1,v2);
            bresenham(v1,v3);
            bresenham(v2,v3);
        }
        else if(mode==Fill)
        {
            edgeWalkingFillRasterization(v1,v2,v3);
        }
    }
}

void Pipeline::clearBuffer(const Vector4D &color, bool depth)
{
    (void)depth;
    m_backBuffer->Fill(color);
}

void Pipeline::setShaderMode(ShadingMode mode)
{
    if(m_shader)delete m_shader;
    if(mode==Simple)
        m_shader=new BasicShader();
    /*else if(mode==Phong)
        ;*/
}

void Pipeline::swapBuffer()
{
    FrameBuffer *tmp=m_frontBuffer;
    m_frontBuffer=m_backBuffer;
    m_backBuffer=tmp;
}

V2F Pipeline::lerp(const V2F &n1, const V2F &n2, float weight)
{
    V2F result;
    result.posV2P=n1.posV2P.lerp(n2.posV2P,weight);
    result.posM2W=n1.posM2W.lerp(n2.posM2W,weight);
    result.color=n1.color.lerp(n2.color,weight);
    result.normal = n1.normal.lerp(n2.normal, weight);
    result.texcoord = n1.texcoord.lerp(n2.texcoord, weight);
    result.oneDivZ=(1.0-weight)*n1.oneDivZ+weight*n2.oneDivZ;
    result.textureID=n1.textureID;
    return result;
}

void Pipeline::bresenham(const V2F &from, const V2F &to)
{
    int dx = to.posV2P.x - from.posV2P.x;
    int dy = to.posV2P.y - from.posV2P.y;
    int sx = 1, sy = 1;
    if(dx < 0)
    {
        sx = -1;
        dx = -dx;
    }
    if(dy < 0)
    {
        sy = -1;
        dy = -dy;
    }
    int nowX = from.posV2P.x;
    int nowY = from.posV2P.y;
    V2F tmp;
    if(dy <= dx)
    {
        int d = 2*dy - dx;
        for(int i = 0;i <= dx;++ i)
        {
            tmp = lerp(from, to, static_cast<double>(i)/dx);
            m_backBuffer->Cover(nowX,nowY,m_shader->fragmentShader(tmp));
            nowX += sx;
            if(d <= 0)
                d += 2*dy;
            else
            {
                nowY += sy;
                d += 2*dy - 2*dx;
            }
        }
    }
    else
    {
        int flag = 2*dx - dy;
        for(int i = 0;i <= dy;++ i)
        {
            tmp = lerp(from, to, static_cast<double>(i)/dy);
            m_backBuffer->Cover(nowX,nowY,m_shader->fragmentShader(tmp));
            nowY += sy;
            if(flag <= 0)
                flag += 2*dx;
            else
            {
                nowX += sx;
                flag -= 2*dy - 2*dx;
            }
        }
    }
}
int Pipeline::getColor(int x,int y,int c)
{
    //if(x<=0||x>=width||y<=0||y>=height)return 0;
    return m_tmp->getColorBuffer()[(y*width+x)*4+c];
}
void Pipeline::scanLinePerRow(const V2F &left, const V2F &right)
{
    V2F current;
    int length = right.posV2P.x - left.posV2P.x + 1;
    for(int i = 0;i <= length;++i)
    {
        double weight = static_cast<double>(i)/length;
        current = lerp(left, right, weight);
        current.posV2P.x = left.posV2P.x + i;
        current.posV2P.y = left.posV2P.y;
        if(current.posV2P.x<0||current.posV2P.x>width||current.posV2P.y<0||current.posV2P.y>height)continue;
        if(current.posV2P.x<=0||current.posV2P.x>width)continue;
        if(current.posV2P.y<=0||current.posV2P.y>height)continue;

        int xx=static_cast<int>(current.posV2P.x);
        int yy=static_cast<int>(current.posV2P.y);
        /*if(current.posV2P.z<m_backBuffer->depth[xx][yy])
        {
            m_backBuffer->Cover(xx,yy,m_shader->fragmentShader(current));
            m_backBuffer->depth[xx][yy]=current.posV2P.z;
        }*/
        /*float big=-0.5;
        float sma=(1-big)/8;
        int off=1;
        current.color.x=getColor(current.posV2P.x-off,current.posV2P.y,0)*sma+
                        getColor(current.posV2P.x,current.posV2P.y-off,0)*sma+
                        getColor(current.posV2P.x+off,current.posV2P.y,0)*sma+
                        getColor(current.posV2P.x,current.posV2P.y+off,0)*sma+
                        getColor(current.posV2P.x-off,current.posV2P.y-off,0)*sma+
                        getColor(current.posV2P.x+off,current.posV2P.y+off,0)*sma+
                        getColor(current.posV2P.x+off,current.posV2P.y-off,0)*sma+
                        getColor(current.posV2P.x-off,current.posV2P.y+off,0)*sma+
                        getColor(current.posV2P.x,current.posV2P.y,0)*big;
        current.color.y=getColor(current.posV2P.x-off,current.posV2P.y,1)*sma+
                        getColor(current.posV2P.x,current.posV2P.y-off,1)*sma+
                        getColor(current.posV2P.x+off,current.posV2P.y,1)*sma+
                        getColor(current.posV2P.x,current.posV2P.y+off,1)*sma+
                        getColor(current.posV2P.x-off,current.posV2P.y-off,1)*sma+
                        getColor(current.posV2P.x+off,current.posV2P.y+off,1)*sma+
                        getColor(current.posV2P.x+off,current.posV2P.y-off,1)*sma+
                        getColor(current.posV2P.x-off,current.posV2P.y+off,1)*sma+
                        getColor(current.posV2P.x,current.posV2P.y,1)*big;
        current.color.z=getColor(current.posV2P.x-off,current.posV2P.y,2)*sma+
                        getColor(current.posV2P.x,current.posV2P.y-off,2)*sma+
                        getColor(current.posV2P.x+off,current.posV2P.y,2)*sma+
                        getColor(current.posV2P.x,current.posV2P.y+off,2)*sma+
                        getColor(current.posV2P.x-off,current.posV2P.y-off,2)*sma+
                        getColor(current.posV2P.x+off,current.posV2P.y+off,2)*sma+
                        getColor(current.posV2P.x+off,current.posV2P.y-off,2)*sma+
                        getColor(current.posV2P.x-off,current.posV2P.y+off,2)*sma+
                        getColor(current.posV2P.x,current.posV2P.y,2)*big;
        current.color.x/=255.0f;current.color.y/=255.0f;current.color.z/=255.0f;current.color.w=1.0f;*/
        if(current.posV2P.z<=m_backBuffer->depth[xx][yy])
        {
            current.color.x=getColor(current.posV2P.x,current.posV2P.y,0)/255.0f;
            current.color.y=getColor(current.posV2P.x,current.posV2P.y,1)/255.0f;
            current.color.z=getColor(current.posV2P.x,current.posV2P.y,2)/255.0f;
            current.color.w=1.0f;
            double w = 1.0/current.oneDivZ;
            current.texcoord *= w;
            m_backBuffer->Cover(current.posV2P.x, current.posV2P.y,
                                 m_shader->fragmentShader(current));
            m_backBuffer->depth[xx][yy]=current.posV2P.z;
        }
    }
}

void Pipeline::rasterTopTriangle(V2F &v1, V2F &v2, V2F &v3)
{
    V2F left = v2;
    V2F right = v3;
    V2F dest = v1;
    V2F tmp, newleft, newright;
    if(left.posV2P.x > right.posV2P.x)
    {
        tmp = left;
        left = right;
        right = tmp;
    }
    int dy = left.posV2P.y - dest.posV2P.y + 1;

    for(int i = 0;i < dy;++i)
    {
        double weight = 0;
        if(dy != 0)
            weight = static_cast<double>(i)/dy;
        newleft = lerp(left, dest, weight);
        newright = lerp(right, dest, weight);
        newleft.posV2P.y = newright.posV2P.y = left.posV2P.y - i;
        scanLinePerRow(newleft, newright);
    }
}

void Pipeline::rasterBottomTriangle(V2F &v1, V2F &v2, V2F &v3)
{
    V2F left = v1;
    V2F right = v2;
    V2F dest = v3;
    V2F tmp, newleft, newright;
    if(left.posV2P.x > right.posV2P.x)
    {
        tmp = left;
        left = right;
        right = tmp;
    }
    int dy = dest.posV2P.y - left.posV2P.y + 1;
    for(int i = 0;i < dy;++i)
    {
        double weight = 0;
        if(dy != 0)
            weight = static_cast<double>(i)/dy;
        newleft = lerp(left, dest, weight);
        newright = lerp(right, dest, weight);
        newleft.posV2P.y = newright.posV2P.y = left.posV2P.y + i;
        scanLinePerRow(newleft, newright);
    }
}

void Pipeline::edgeWalkingFillRasterization(const V2F &v1, const V2F &v2, const V2F &v3)
{
    V2F tmp;
    V2F target[3] = {v1, v2,v3};
    if(target[0].posV2P.y > target[1].posV2P.y)
    {
        tmp = target[0];
        target[0] = target[1];
        target[1] = tmp;
    }
    if(target[0].posV2P.y > target[2].posV2P.y)
    {
        tmp = target[0];
        target[0] = target[2];
        target[2] = tmp;
    }
    if(target[1].posV2P.y > target[2].posV2P.y)
    {
        tmp = target[1];
        target[1] = target[2];
        target[2] = tmp;
    }
    if(target[0].posV2P.y==target[1].posV2P.y)
    {
        rasterBottomTriangle(target[0],target[1],target[2]);
    }
    else if(target[1].posV2P.y==target[2].posV2P.y)
    {
        rasterTopTriangle(target[0], target[1], target[2]);
    }
    else
    {
        double weight = static_cast<double>(target[1].posV2P.y-target[0].posV2P.y)/(target[2].posV2P.y-target[0].posV2P.y);
        V2F newPoint = lerp(target[0],target[2],weight);
        newPoint.posV2P.y = target[1].posV2P.y;
        rasterTopTriangle(target[0], newPoint, target[1]);
        rasterBottomTriangle(newPoint,target[1],target[2]);
    }
}
