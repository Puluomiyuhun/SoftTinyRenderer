#include "framebuffer.h"

void FrameBuffer::Fill(Vector4D vec){
    unsigned char cl[4];
    cl[0]=static_cast<unsigned char>(vec.x*255);
    cl[1]=static_cast<unsigned char>(vec.y*255);
    cl[2]=static_cast<unsigned char>(vec.z*255);
    cl[3]=static_cast<unsigned char>(vec.w*255);
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            for(int k=0;k<4;k++){
                mp[(i*width+j)*4+k]=cl[k];
            }
            depth[j][i]=10055;
        }
    }
}
void FrameBuffer::Cover(int x,int y,Vector4D vec){
    unsigned char cl[4];
    cl[0]=static_cast<unsigned char>(vec.x*255);
    cl[1]=static_cast<unsigned char>(vec.y*255);
    cl[2]=static_cast<unsigned char>(vec.z*255);
    cl[3]=static_cast<unsigned char>(vec.w*255);
    for(int k=0;k<4;k++){
        mp[(y*width+x)*4+k]=cl[k];
    }
}
unsigned char* FrameBuffer::getColorBuffer(){
    return mp;
}
