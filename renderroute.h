#ifndef RENDERROUTE_H
#define RENDERROUTE_H
#include"QObject"
#include "pipeline.h"

class RenderRoute:public QObject
{
    Q_OBJECT
public:
    explicit RenderRoute(int w,int h,QObject *parent=nullptr);
    ~RenderRoute(){}
    void stopIt();
signals:
    void frameOut(unsigned char *image);

public slots:
    void loop();

private:
    bool stopped;
    int width,height,channel;
    Pipeline *pipeline;
};

#endif
