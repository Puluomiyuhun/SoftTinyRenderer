#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "vector4d.h"

class FrameBuffer
{
private:
    int width,height;
    unsigned char mp[8294405];
public:
    float depth[1925][1085];
public:
    FrameBuffer(int w,int h):width(w),height(h){}
    ~FrameBuffer(){}
    void Fill(Vector4D vec);
    void Cover(int x,int y,Vector4D vec);
    unsigned char *getColorBuffer();
};

#endif // FRAMEBUFFER_H
