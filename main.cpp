#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(QString(":/buttons/icon.png")));
    Widget w;
    w.show();
    w.showFullScreen();

    return a.exec();
}
