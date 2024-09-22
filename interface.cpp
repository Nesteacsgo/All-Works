#include "interface.h"

#include "classfunctions.h"

#include "iostream"


Interface::Interface() {
    std::cout << "Welcome in ToDoList!\n"
                "For out commands input help\n";
    userIn();
}
void Interface::userIn() {
    std::getline(std::cin,userInput);
    checkUserMessage();
}
void Interface::help() {
    std::cout << "\n"
                 "Output tasks:\n"
                "all: list\n"
                "new: list -s new\n"
                "in progress: list -s in_progress\n"
                "done: list -s done\n\n"
                "Operation with tasks:\n"
                "change status on complete: complete\n"
                "change status on in_progress: in_progress\n"
                "create task: new id\n"
                "change task: edit id\n"
                "delete task: delete id\n"
                "output commands: help"
                 "\n";
}

void Interface::exit() {
    std::exit(EXIT_SUCCESS);
}
void Interface::checkUserMessage() {
    switch(commands.indexOf(userInput)) {
    case 0:
        exit();
        break;
    case 1:
        task.showTasksAll();
        break;
    case 2:
        task.showTasksWithParameter("new");
        break;
    case 3:
        task.showTasksWithParameter("in_progress");
        break;
    case 4:
        task.showTasksWithParameter("done");
        break;
    case 5:
        help();
        break;
    case 6:
        task.changeStatus(QString(ClassFunctions::inputId()).toInt(), "done");
        break;
    case 7:
        task.changeStatus(QString(ClassFunctions::inputId()).toInt(), "in_progress");
        break;
    case 8:
        task.taskNew(ClassFunctions::inputUserData(tags[3]),
                ClassFunctions::inputUserData(tags[2]).toInt(),
                ClassFunctions::inputUserData(tags[1]),
                ClassFunctions::inputUserData(tags[0]));
        break;
    case 9:
        task.taskEdit(QString(ClassFunctions::inputId()).toInt());
        break;
    case 10:
        task.taskDelete(QString(ClassFunctions::inputId()).toInt());
        break;
    default:
        std::cout << "Unknown command, try again!!!\n";
    }
    userIn();
}


