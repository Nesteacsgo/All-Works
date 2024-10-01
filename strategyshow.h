#ifndef STRATEGYSHOW_H
#define STRATEGYSHOW_H

#include "iostream"
#include "receiver.h"

#include <QDebug>

class StrategyShow
{
public:
    StrategyShow();
    Receiver *receiver = new Receiver;
    virtual void execute() const = 0;
};

class ShowAllTasks : public StrategyShow {
public:
    void execute() const override {
        receiver->openFileForRead();
        receiver->readFileXML();


        for (int i = 0; i < receiver->getDataSize(); i++) {
            if (receiver->isElementDeleted(receiver->getElement(i,"Deadline"))) {
                continue;
            }
            else {
                receiver->outputTasks(i);
            }

        }
        receiver->closeFile();
    };
};

class ShowNewTasks : public StrategyShow {
public:
    void execute() const override {
        receiver->openFileForRead();
        receiver->readFileXML();
        int count = 0;

        for (int i = 0; i < receiver->getDataSize(); i++) {
            if ((receiver->getElement(i,"Status").text() == "new") && (!receiver->isElementDeleted(receiver->getElement(i,"Deadline")))) {
                receiver->outputTasks(i);
                count++;
            }
            else {
                continue ;
            }
        }
        if (count == 0) {
            qDebug() << "Tasks with this parameter not found!\n";
            receiver->closeFile();
            return;
        }
        receiver->closeFile();
    };
};
class ShowInProgressTasks : public StrategyShow {
public:
    void execute() const override {
        receiver->openFileForRead();
        receiver->readFileXML();
        int count = 0;

        for (int i = 0; i < receiver->getDataSize(); i++) {
            if ((receiver->getElement(i,"Status").text() == "in_progress") && (!receiver->isElementDeleted(receiver->getElement(i,"Deadline")))) {
                receiver->outputTasks(i);
                count++;
            }
            else {
                continue ;
            }
        }
        if (count == 0) {
            qDebug() << "Tasks with this parameter not found!\n";
            receiver->closeFile();
            return;
        }
        receiver->closeFile();
    };
};
class ShowDoneTasks : public StrategyShow {
public:
    void execute() const override {
        receiver->openFileForRead();
        receiver->readFileXML();
        int count = 0;

        for (int i = 0; i < receiver->getDataSize(); i++) {
            if ((receiver->getElement(i,"Status").text() == "done") && (!receiver->isElementDeleted(receiver->getElement(i,"Deadline")))) {
                receiver->outputTasks(i);
                count++;
            }
            else {
                continue ;
            }
        }
        if (count == 0) {
            qDebug() << "Tasks with this parameter not found!\n";
            receiver->closeFile();
            return;
        }
        receiver->closeFile();
    };
};

#endif // STRATEGYSHOW_H
