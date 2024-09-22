#ifndef INTERFACE_H
#define INTERFACE_H

#include "task.h"

#include <QVector>
#include <QOBject>
#include <QCoreApplication>


class Interface
{
public:
    Interface();

    void help();
    void exit();

    void checkUserMessage();
    void userIn();

    Task task;
    std::string userInput;
    QVector<std::string> commands{"exit","list","list -s new","list -s in_progress", "list -s done", "help","complete","in_progress","new", "edit", "delete"};
    QVector<QString> tags{"Caption","Description","Priority","Deadline"};


};

#endif // INTERFACE_H
