#ifndef INTERFACE_H
#define INTERFACE_H

#include "command.h"
#include "strategyshow.h"

#include <QVector>

class Interface
{
private:
    Command *editTask;
    Command *editStatusTask;
    Command *newTask;
    Command *deleteTask;
    Command *help;
    Command *exit;
    Command *input;
    Command* getStr;

    StrategyShow *strategyShow;

    Receiver *receiver = new Receiver;
public:
    Interface();


    void setStrategyShow(StrategyShow *strategy) {
        strategyShow = strategy;
    }
    void setNewTask(Command *command) {
        newTask = command;
    }
    void setEditTask(Command *command) {
        editTask = command;
    }
    void setEditStatusTask(Command *command) {
        editStatusTask = command;
    }
    void setDeleteTask(Command *command) {
        deleteTask = command;
    }
    void setHelp(Command *command) {
        help = command;
    }
    void setExit(Command *command) {
        exit = command;
    }
    void setInput(Command *command) {
        input = command;
    }

    void callStart();

    void callExitExec();
    void callHelpExec();
    void callEditStatusTask();
    void callNewTask();
    void callEditTask();
    void callDeleteTask();

    void checkUserMessage(std::string str);
    void userInput();
    std::string inputUserData(std::string tag);
    std::string inputId();

    QVector<std::string> commands{"exit","list","list -s new","list -s in_progress", "list -s done", "help","complete","in_progress","new", "edit", "delete"};

};

#endif // INTERFACE_H
