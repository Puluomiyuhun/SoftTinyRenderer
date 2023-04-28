#ifndef TEXTURE_H
#define TEXTURE_H
#include"vector2d.h"
#include"vector4d.h"
#include<QMainWindow>
#include <QString>

class Textures
{
private:
    int width,height,channel;
    QImage *pixelBuffer;
public:
    Textures();
    ~Textures();
    void loadImage(const QString &path);
    Vector4D sample(const Vector2D &texcoord);
};

#endif // TEXTURE_H
