#include <QApplication>
#include <viewwidget.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewWidget view;
    view.setWindowTitle("Лагуткина М.");
    view.show();
    return a.exec();
}
