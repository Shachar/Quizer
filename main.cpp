#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("Shachar Shemesh");
    a.setOrganizationDomain("shemesh.biz");
    a.setApplicationName("Quizer");
    a.setLayoutDirection(Qt::LeftToRight);

    MainWindow w;
    w.show();

    return a.exec();
}
