#include "receiver.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDate>
using namespace std;

Receiver::Receiver() {
    file->setFileName(QCoreApplication::applicationDirPath()+ "/Tasks.xml");
}

void Receiver::Help() {
    cout << "\n"
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

void Receiver::Exit() {
    std::exit(EXIT_SUCCESS);
}

void Receiver::EditStatusTask(std::string status, std::string id) {
    openFileForRead();
    readFileXML();


    int idTask = findTaskPosition(QString::fromStdString(id).toInt());

    if (isElementDeleted(getElement(idTask,"Deadline"))) {
        qDebug() << "Task already deleted, change is blocked.";
        closeFile();
        return ;
    }
    if (data.at(idTask).lastChildElement("Status").text() == "done") {
        qDebug() << "Task completed, changing status has been blocked.\n";
        closeFile();
        return ;
    }
    else {
        if (status == "done") {
            data.at(idTask).appendChild(createTaskTag("Complete", QString(QDate::currentDate().toString("dd.MM.yyyy")).toStdString()));
        }
    }
    data.at(idTask).replaceChild(createTaskTag("Status",status),
                                 data.at(idTask).lastChildElement("Status"));
    saveDoc();
}

void Receiver::EditTask(QVector <std::string>* taskData, std::string id) {
    openFileForRead();
    readFileXML();
    int idTask = findTaskPosition(QString::fromStdString(id).toInt());

    if (isElementDeleted(getElement(idTask,"Deadline"))) {
        qDebug() << "Task already deleted, change is blocked.";
        closeFile();
        return ;
    }
    if (data.at(idTask).lastChildElement("Status").text() == "done") {
        qDebug() << "Task completed, changing status has been blocked.\n";
        closeFile();
        return ;
    }
    for (int i = 0; i < 4; i++) {
        if (taskData->at(i) == "-") {
            continue;
        }
        data.at(idTask).replaceChild(createTaskTag(tags[i],taskData->at(i)), data.at(idTask).lastChildElement( QString::fromStdString(tags[i])) );
    }
    saveDoc();
}

void Receiver::NewTask(QVector <std::string>* taskData) {
    openFileForRead();
    setDocContent();

    QDomElement root = doc->documentElement();
    doc->appendChild(root);

    QDomElement task = doc->createElement("Task");
    QDomAttr id = doc->createAttribute("id");


    QString num = QString::number(doc->elementsByTagName("Task").size());
    id.setValue(QString::number(num.toInt()+1));
    task.setAttributeNode(id);

    for (int i = 0; i < 4; i++) {
        task.appendChild(createTaskTag(tags[i], taskData->at(i)));
    }
    task.appendChild(createTaskTag("Status", "new"));

    root.appendChild(task);

    saveDoc();
    qDebug() << "Successfull save";


}
void Receiver::DeleteTask(std::string id) {
    openFileForRead();
    readFileXML();

    int idTask = findTaskPosition(QString::fromStdString(id).toInt());

    for (int i = 0; i < 6; i++) {
        data.at(idTask).replaceChild(createTaskTag(tags[i],"deleted"), data.at(idTask).lastChildElement( QString::fromStdString(tags[i])) );
    }
    saveDoc();
}


void Receiver::setStr(std::string s) {
    str = s;
}
std::string Receiver::getStr() {
    return str;
}


void Receiver::openFileForRead() {
    if (file->isOpen()) {
        file->close();
    }
    if(!file->open(QIODevice::ReadOnly)) {
        qDebug() << "File for reading not open";
        return ;
    }
    else {
        qDebug() << "File for reading opened";
    }
}

void Receiver::openFileForWrite() {
    if (file->isOpen()) {
        file->close();
    }
    if(!file->open(QIODevice::WriteOnly)) {
        qDebug() << "File for writing not open";
        return ;
    }
    else {
        qDebug() << "File for writing opened";
    }
}

void Receiver::setDocContent() {
    doc->setContent(file);
}
void Receiver::readFileXML() {
    setDocContent();
    data = doc->elementsByTagName("Task");
}

void Receiver::saveDoc() {
    openFileForWrite();
    file->resize(0);
    QTextStream out(file);
    doc->save(out,4);

    closeFile();
}

void Receiver::outputTasks(int id) {
    qDebug() << "Id: " << data.at(id).attributes().namedItem("id").nodeValue().toInt();
    qDebug() << "Caption: " << data.at(id).lastChildElement("Caption").text();
    qDebug() << "Description: " << data.at(id).lastChildElement("Description").text();
    qDebug() << "Priority: " << data.at(id).lastChildElement("Priority").text().toInt();
    qDebug() << "Deadline: " << data.at(id).lastChildElement("Deadline").text();
    qDebug() << "Status: " << data.at(id).lastChildElement("Status").text();
    qDebug() << "Complete: " << (data.at(id).lastChildElement("Complete").text() = "" ?  data.at(id).lastChildElement("Complete").text() : "-");
    qDebug() << "\n";
}

bool Receiver::isElementDeleted(QDomElement el) {
    if (el.text() == "deleted") {
        return true;
    }
    return false;
}

QDomElement Receiver::createTaskTag (std::string tag, std::string tagValue) {
    QDomElement el = doc->createElement(QString::fromStdString(tag));
    el.appendChild(doc->createTextNode(QString::fromStdString(tagValue)));

    return el;
}

int Receiver::findTaskPosition(int idTask) {
    for (int i = 0; i < getDataSize(); ++i) {
        if (idTask == data.at(i).attributes().namedItem("id").nodeValue().toInt()) {
            return i;
        }
    }
    return 0;
}

QDomElement Receiver::getElement(int id, QString tag) {
    return data.at(id).lastChildElement(tag);
}
int Receiver::getDataSize() {
    return data.count();
}

void Receiver::closeFile() {
    file->close();
}



bool Receiver::checkPriorityOnValid(QString num) {
    if ((num == "-") || (0 < num.toInt() && num.toInt() <= 10)) {
        return true;
    }
    else {
        qDebug() << "Wrong priority, try again!\n";
        return false;
    }
}

bool Receiver::checkDeadlineOnValid(QString date) {
    std::stringstream ss(date.toStdString());
    std::string dateDays;
    std::string dateMonth;
    std::string dateYear;

    if (date.contains('/')) {
        std::getline(ss,dateDays,'/');
        std::getline(ss,dateMonth,'/');
        std::getline(ss,dateYear,'/');
    }
    else {
        std::getline(ss,dateDays,'.');
        std::getline(ss,dateMonth,'.');
        std::getline(ss,dateYear,'.');
    }

    if (date == "-" || (checkDays(QString::fromStdString(dateDays).toInt(),(QString::fromStdString(dateMonth).toInt())) &&
                                             checkMonth(QString::fromStdString(dateMonth).toInt()) &&
                                             checkYear(QString::fromStdString(dateYear).toInt()))) {
        return true;
    }
    else {
        qDebug() << "Wrong date, try again!";
        return false;
    }
}

bool Receiver::checkDays(int days, int month) {
    if (QVector <int> {1,3,5,7,8,10,12}.contains(month)) {
        if (days > 0 && days <=31) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (month == 2) {
        if (days > 0 && days <= 28) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if (days > 0 && days <=30) {
            return true;
        }
        else {
            return false;
        }
    }
}

bool Receiver::checkMonth(int month) {
    if (month > 0 && month <= 12) {
        return true;
    }
    else {
        return false;
    }

}

bool Receiver::checkYear(int year) {
    if (year >= QDate::currentDate().toString("yyyy").toInt() && year < 2200) {
        return true;
    }
    else {
        return false;
    }
}
