#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QFile>
#include <QVector>
#include <QDomDocument>
class Task
{
private:
    QString Caption;
    QString Description;
    int Priority;
    QString Deadline;
    QString Status;
    QString CompleteDate;

public:
    Task();

    QString getCaption();
    QString getDescription();
    int getPriority();
    QString getDeadline();
    QString getStatus();
    QString getTaskCompleteDate();

    void setCaption(QString);
    void setDescription(QString);
    void setPriority(int);
    void setDeadline(QString);
    void setStatus(QString);
    void setTaskCompleteDate(QString);


    void showTasksAll();
    void showTasksWithParameter(QString);
    void taskNew(QString title,int priority,QString text, QString dateFinish);
    void taskEdit(int id);
    void changeStatus(int id, QString status);
    void taskDelete(int id);


    int findTaskWithId(int inputId, QDomNodeList &data);
    void saveTask();
    void changeData(int id, QString tagName, QString newTagValue, QDomDocument &doc);
    QDomNodeList readFileXML(QFile &file);
    void outputTasks(QDomNodeList &data, int id);
    bool isDeleted(QDomElement el);
    QDomElement createElement(QString tag, QString tagValue, QDomDocument &doc);
    void getAllData(QVector <QString> &v);

    void saveDoc(QDomDocument &doc);

    QVector<QString> tags{"Caption", "Description", "Priority", "Deadline", "Status", "Complete"};
    QFile file;

};



#endif // TASK_H
