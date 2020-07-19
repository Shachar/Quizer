#include "AlgebraWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlgebraWindow w;
    w.show();

    return a.exec();
}
