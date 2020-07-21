#include "AlgebraWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("Shachar Shemesh");
    a.setOrganizationDomain("shemesh.biz");
    a.setApplicationName("Quizer");

    QSettings settings;

    AlgebraWindow w(settings);
    w.show();

    return a.exec();
}
