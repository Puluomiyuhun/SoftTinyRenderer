#include "textures.h"
#include "QDebug"

Textures::Textures()
{
    width=0;
    height=0;
    channel=0;
    pixelBuffer=nullptr;
}

void Textures::loadImage(const QString &path)
{
    pixelBuffer=new QImage();
    pixelBuffer->load(path);
    width=pixelBuffer->width();
    height=pixelBuffer->height();
    channel=3;
}

Vector4D Textures::sample(const Vector2D &texcoord)
{
    Vector4D result(0.0,0.0,0.0,1.0);
    unsigned int x = 0, y = 0;
    double factorU = 0, factorV = 0;
    if(texcoord.x >= 0.0f && texcoord.x <= 1.0f && texcoord.y >= 0.0f && texcoord.y <= 1.0f)
    {
        double trueU = texcoord.x * (width - 1);
        double trueV = texcoord.y * (height - 1);
        x = static_cast<unsigned int>(trueU);
        y = static_cast<unsigned int>(trueV);
        factorU = trueU - x;
        factorV = trueV - y;
    }
    else
    {
        float u = texcoord.x,v = texcoord.y;
        if(texcoord.x > 1.0f)
            u = texcoord.x - static_cast<int>(texcoord.x);
        else if(texcoord.x < 0.0f)
            u = 1.0f - (static_cast<int>(texcoord.x) - texcoord.x);
        if(texcoord.y > 1.0f)
            v = texcoord.y - static_cast<int>(texcoord.y);
        else if(texcoord.y < 0.0f)
            v = 1.0f - (static_cast<int>(texcoord.y) - texcoord.y);

        double trueU = u * (width - 1);
        double trueV = v * (height - 1);
        x = static_cast<unsigned int>(trueU);
        y = static_cast<unsigned int>(trueV);
        factorU = trueU - x;
        factorV = trueV - y;
    }
    Vector3D texels[4];

    pixelBuffer->pixelColor(x,y).red();
    texels[0].x = static_cast<float>(pixelBuffer->pixelColor(x,y).red()) * 1.0f/255;
    texels[0].y = static_cast<float>(pixelBuffer->pixelColor(x,y).green()) * 1.0f/255;
    texels[0].z = static_cast<float>(pixelBuffer->pixelColor(x,y).blue()) * 1.0f/255;

    /*texels[1].x = static_cast<float>(pixelBuffer->pixelColor(x,y+1).red()) * 1.0f/255;
    texels[1].y = static_cast<float>(pixelBuffer->pixelColor(x,y+1).green()) * 1.0f/255;
    texels[1].z = static_cast<float>(pixelBuffer->pixelColor(x,y+1).blue()) * 1.0f/255;

    texels[2].x = static_cast<float>(pixelBuffer->pixelColor(x+1,y+1).red()) * 1.0f/255;
    texels[2].y = static_cast<float>(pixelBuffer->pixelColor(x+1,y+1).green()) * 1.0f/255;
    texels[2].z = static_cast<float>(pixelBuffer->pixelColor(x+1,y+1).blue()) * 1.0f/255;

    texels[3].x = static_cast<float>(pixelBuffer->pixelColor(x+1,y).red()) * 1.0f/255;
    texels[3].y = static_cast<float>(pixelBuffer->pixelColor(x+1,y).green()) * 1.0f/255;
    texels[3].z = static_cast<float>(pixelBuffer->pixelColor(x+1,y).blue()) * 1.0f/255;

    texels[0] = texels[0] * (1.0 - factorU) + texels[3] * factorU;
    texels[1] = texels[1] * (1.0 - factorU) + texels[2] * factorU;

    result = texels[0] * (1.0 - factorV) + texels[1] *factorV;*/
    result = texels[0];

    return result;
}

