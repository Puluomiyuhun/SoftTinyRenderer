#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QThread"
#include "QTimer"
#include "pipeline.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1280,768);
    setFixedSize(1280,768);
    loop=new RenderRoute(width(),height(),nullptr);
    loopThread=new QThread(this);
    loop->moveToThread(loopThread);
    connect(loopThread,&QThread::finished,loop, &RenderRoute::deleteLater);
    connect(loopThread,&QThread::started,loop,&RenderRoute::loop);
    connect(loop,&RenderRoute::frameOut,this,&MainWindow::receiveFrame);
    loopThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    loop->stopIt();
    loopThread->quit();
    loopThread->wait();
    if(canvas)delete canvas;
    if(loopThread)delete loopThread;
    loop=nullptr;
    canvas=nullptr;
    loopThread=nullptr;
}

void MainWindow::receiveFrame(unsigned char *data)
{
    if(canvas) delete canvas;
    canvas = new QImage(data, width(), height(), QImage::Format_RGBA8888);
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if(canvas)
    {
        QPainter painter(this);
        painter.drawImage(0,0,*canvas);
    }
    QWidget::paintEvent(event);
}
