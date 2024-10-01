#ifndef COMMAND_H
#define COMMAND_H

#include "receiver.h"

#include <QDebug>

class Command
{
public:
    Command();
    virtual void execute() const = 0;
};


class CommandNewTask : public Command {
private:
    Receiver *receiver;
    QVector <std::string> *taskData = new QVector <std::string>;
public:
    explicit CommandNewTask(Receiver *receiverNew, std::string caption, std::string description, std::string priority, std::string deadline)
        {
            receiver = receiverNew;
            taskData->push_back(caption);
            taskData->push_back(description);
            taskData->push_back(priority);
            taskData->push_back(deadline);
        } ;
    void execute() const override {
        if (receiver->checkPriorityOnValid( QString::fromStdString(taskData->at(2)) ) && receiver->checkDeadlineOnValid( QString::fromStdString(taskData->at(3)) )) {
            receiver->NewTask(taskData);
        }
        else {
            qDebug() << "Wrong data, try again";
            return;
        }
    };
};

class CommandHelp : public Command {
private:
    Receiver *receiver;
public:
    explicit CommandHelp(Receiver *receiver) : receiver(receiver) {} ;
    void execute() const override {
        receiver->Help();
    };
};

class CommandExit : public Command {
private:
    Receiver *receiver;
public:
    explicit CommandExit(Receiver *receiver) : receiver(receiver) {} ;
    void execute() const override {
        receiver->Exit();
    };
};

class CommandEditStatusTask : public Command {
private:
    std::string id;
    std::string status;
    Receiver *receiver;
public:
    explicit CommandEditStatusTask(Receiver *receiver, std::string status, std::string id) :  id(id), status(status), receiver(receiver) {} ;
    void execute() const override {
        receiver->EditStatusTask(status, id);
    };
};

class CommandEditTask : public Command {
private:
    Receiver *receiver;
    QVector <std::string> *taskData = new QVector <std::string>;
    std::string id;
public:
    explicit CommandEditTask(Receiver *receiverNew, std::string idNew, std::string caption, std::string description, std::string priority, std::string deadline)
        {
        receiver = receiverNew;
        taskData->push_back(caption);
        taskData->push_back(description);
        taskData->push_back(priority);
        taskData->push_back(deadline);
        id = idNew;
        } ;
    void execute() const override {
        if (receiver->checkPriorityOnValid( QString::fromStdString(taskData->at(2)) ) && receiver->checkDeadlineOnValid( QString::fromStdString(taskData->at(3)) )) {
            receiver->EditTask(taskData, id);
        }
        else {
            qDebug() << "Wrong data, try command again";
            return;
        }
    }
};

class CommandDeleteTask : public Command {
private:
    std::string id;
    Receiver *receiver;
public:
    explicit CommandDeleteTask(Receiver *receiver, std::string id) : id(id), receiver(receiver) {};
    void execute() const override {
        receiver->DeleteTask(id);
    }
};
#endif // COMMAND_H
