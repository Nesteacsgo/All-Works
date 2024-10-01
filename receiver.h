#ifndef RECEIVER_H
#define RECEIVER_H

#include "iostream"

#include <QDomDocument>
#include <QFile>

struct TaskData {
    std::string caption;
    std::string description;
    std::string priority;
    std::string deadline;
};

class Receiver
{
private:
    std::string str;

    QDomDocument *doc = new QDomDocument;
    QDomNodeList data;
    QFile *file = new QFile;

    QVector <std::string> tags = {"Caption", "Description", "Priority", "Deadline","Status", "Complete"};
public:
    Receiver();
    void NewTask(QVector <std::string>* taskData);
    void EditTask(QVector <std::string>* taskData, std::string id);
    void DeleteTask(std::string id);
    void EditStatusTask(std::string status, std::string id);
    void Help();
    void Exit();
    void Input();
    void checkUserMessage(std::string msg);

    void setStr(std::string);
    std::string getStr();
    QDomElement getElement(int id, QString status);
    int getDataSize();
    void closeFile();


    void openFileForRead();
    void openFileForWrite();
    void setDocContent();
    void readFileXML();
    void outputTasks(int id);
    bool isElementDeleted(QDomElement el);
    int findTaskPosition(int idTask);
    QDomElement createTaskTag(std::string tag, std::string tagValue);
    void saveDoc();

    bool checkPriorityOnValid(QString num);
    bool checkDeadlineOnValid(QString date);

    bool checkDays(int days, int month);
    bool checkMonth(int month);
    bool checkYear(int year);
};



#endif // RECEIVER_H

