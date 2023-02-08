#include"splineview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SplineView spl;
    spl.setWindowTitle("Laborotory work №7");
    spl.show();
    return a.exec();
}
