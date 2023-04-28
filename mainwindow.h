#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderroute.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected slots:
    void receiveFrame(unsigned char *image);

private:
    void paintEvent(QPaintEvent *) override;

private:
    Ui::MainWindow *ui;
    QImage *canvas;
    QTimer *timer;
    QThread *loopThread;
    RenderRoute *loop;
};
#endif // MAINWINDOW_H
