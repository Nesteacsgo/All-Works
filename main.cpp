#include <QCoreApplication>
#include "interface.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Interface *interface = new Interface;
    interface->callStart();

    return a.exec();
}
