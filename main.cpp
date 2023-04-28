#include "mainwindow.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "matrix.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
