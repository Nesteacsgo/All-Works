#include "interface.h"

Interface::Interface() {}

void Interface::callStart() {
    std::cout << "Welcome in ToDoList!\n"
                 "For out commands input help\n";
    userInput();

}

void Interface::userInput() {
    std::string s;
    std::getline(std::cin,s);
    checkUserMessage(s);
}
std::string Interface::inputUserData(std::string tag) {
    std::cout << "Enter the "+ tag +" : ";
    std::string  userInput;
    std::getline(std::cin,userInput);
    return userInput;
}
std::string Interface::inputId() {
    std::string id;
    std::cout << "Enter id\n";
    std::getline(std::cin,id);
    return id;
}

void Interface::callHelpExec() {

    this->help->execute();
}
void Interface::callExitExec() {
    this->exit->execute();
}
void Interface::callEditStatusTask() {
    this->editStatusTask->execute();
}
void Interface::callNewTask() {
    this->newTask->execute();
}
void Interface::callEditTask() {
    this->editTask->execute();
}
void Interface::callDeleteTask() {
    this->deleteTask->execute();
}

void Interface::checkUserMessage(std::string str) {

    switch(commands.indexOf(str)) {
    case 0: // exit
        this->setExit(new CommandExit(receiver));
        callExitExec();
        break;
    case 1: // show all tasks
        setStrategyShow(new ShowAllTasks);
        this->strategyShow->execute();
        break;
    case 2: // show new tasks
        setStrategyShow(new ShowNewTasks);
        this->strategyShow->execute();
        break;
    case 3: // show in_progress tasks
        setStrategyShow(new ShowInProgressTasks);
        this->strategyShow->execute();
        break;
    case 4: // show complete tasks
        setStrategyShow(new ShowDoneTasks);
        this->strategyShow->execute();
        break;
    case 5: // help
        this->setHelp(new CommandHelp(receiver));
        callHelpExec();
        break;
    case 6: // edit status on done
        this->setEditStatusTask(new CommandEditStatusTask(receiver,"done", inputId()));
        callEditStatusTask();
        break;
    case 7: // edit status on in_progress
        this->setEditStatusTask(new CommandEditStatusTask(receiver,"in_progress", inputId()));
        callEditStatusTask();
        break;
    case 8: // new task
        this->setNewTask(new CommandNewTask(receiver,
                                            inputUserData("Caption"),
                                            inputUserData("Description"),
                                            inputUserData("Priority"),
                                            inputUserData("Deadline")));
        callNewTask();
        break;
    case 9: // edit task
        qDebug() << "If you don`t want to change anything parameter, enter '-'";
        this->setEditTask(new CommandEditTask(receiver,
                                            inputId(),
                                            inputUserData("Caption"),
                                            inputUserData("Description"),
                                            inputUserData("Priority"),
                                            inputUserData("Deadline")
                                              ));
        callEditTask();
        break;
    case 10: // delete task
        this->setDeleteTask(new CommandDeleteTask(receiver,inputId()));
        callDeleteTask();
        break;
    default:
        std::cout << "Unknown command, try again!!!\n";
    }
    userInput();
}
