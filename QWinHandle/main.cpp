#include "QWinHandle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWinHandle w;
    w.show();

    return a.exec();
}
