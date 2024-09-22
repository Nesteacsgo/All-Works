#include "task.h"
#include "classfunctions.h"

#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QDate>

Task::Task() {
    file.setFileName("F:\\Tasks.xml");
}

// ГЕТТЕРЫ И СЕТТЕРЫ
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
QString Task::getCaption() {
    return Caption;
}
QString Task::getDescription() {
    return Description;
}
int Task::getPriority() {
    return Priority;
}
QString Task::getDeadline() {
    return Deadline;
}
QString Task::getStatus() {
    return Status;
}
QString Task::getTaskCompleteDate() {
    return CompleteDate;
}


void Task::setCaption(QString str) {
    Caption = str;
}
void Task::setDescription(QString str) {
    Description = str;
}
void Task::setPriority(int num) {
    Priority = num;
}
void Task::setDeadline(QString date) {
    Deadline = date;
}
void Task::setStatus(QString status) {
    Status = status;
}
void Task::setTaskCompleteDate(QString date) {
    CompleteDate = date;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ОПЕРАЦИИ НАД ЗАДАЧАМИ И ИХ ДАННЫМИ
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Занесение новой задачи в XML-файле
void Task::saveTask() {
    ClassFunctions::openForReadFile(file);

    QDomDocument doc;
    doc.setContent(&file);

    QDomElement root = doc.documentElement();
    doc.appendChild(root);

    QDomElement task = doc.createElement("Task");
    QDomAttr id = doc.createAttribute("id");

    QString num = root.lastChild().toElement().attribute(QString("id"));
    num = QString::number(doc.elementsByTagName("Task").size());

    id.setValue(QString::number(num.toInt()+1));
    task.setAttributeNode(id);

    QVector <QString> v;
    getAllData(v);

    for (int i = 0; i < v.size(); i++) {
        task.appendChild(createElement(tags[i],v[i],doc));
    }
    root.appendChild(task);

    saveDoc(doc);
    qDebug() << "Successfull save";


}

// Создание новой задачи
void Task::taskNew(QString dateFinish, int priority, QString text, QString title) {
    setCaption(title);
    setDescription(text);
    setStatus("new");
    while (true) {
        if (ClassFunctions::checkPriorityOnValid(QString::number(priority))) {
            setPriority(priority);
            break;
        }
        else priority = ClassFunctions::inputUserData("Priority").toInt();
    }
    while (true) {
        if (ClassFunctions::checkDeadlineOnValid(dateFinish)) {
            setDeadline(dateFinish);
            break;
        }
        else dateFinish = ClassFunctions::inputUserData("Deadline");
    }

    saveTask();
}

// Изменение данных в задаче
void Task::taskEdit(int id) {



    ClassFunctions::openForReadFile(file);
    QDomDocument doc;


    doc.setContent(&file);
    QDomNodeList data = doc.elementsByTagName("Task");

    if (isDeleted(data.at(findTaskWithId(id,data)).lastChildElement("Deadline"))) {
        qDebug() << "Task already deleted, change is blocked.";
        return ;
    }
    qDebug() << "If you don`t want to change anything parameter, enter '-'";
    for (int i = 0; i < 4; i++) {
        changeData(id,tags[i],ClassFunctions::inputUserData(tags[i]),doc);
    }

    saveDoc(doc);

}
// Удаление задачи(Структура остается, данные приравниваются к deleted)
void Task::taskDelete(int id) {
    ClassFunctions::openForReadFile(file);

    QDomDocument doc;
    doc.setContent(&file);

    for (int i = 0; i < 6; i++) {
        changeData(id,tags[i],"deleted",doc);
    }
    saveDoc(doc);
}

// Изменение статуса на in_progress или done
void Task::changeStatus(int id,QString status) {
    ClassFunctions::openForReadFile(file);


    QDomDocument doc;
    doc.setContent(&file);
    QDomNodeList data = doc.elementsByTagName("Task");
    int idTask = findTaskWithId(id,data);

    if (isDeleted(data.at(idTask).lastChildElement("Deadline"))) {
        qDebug() << "Task already deleted, change is blocked.";
        return ;
    }
    if (data.at(idTask).lastChildElement("Status").text() == "done") {
        qDebug() << "Task completed, changing status has been blocked.\n";
        file.close();
        return ;
    }
    else {
        if (status == "done") {
            data.at(idTask).appendChild(createElement("Complete",QDate::currentDate().toString("dd.MM.yyyy"),doc));
        }
    }
    data.at(idTask).replaceChild(createElement("Status",status,doc),data.at(idTask).lastChildElement("Status"));

    saveDoc(doc);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ВЫВОД ЗАДАЧ
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Вывод всех задач
void Task::showTasksAll() {

    ClassFunctions::openForReadFile(file);

    QDomNodeList data = readFileXML(file);

    for (int i = 0; i < data.count(); i++) {
        if (isDeleted(data.at(i).lastChildElement("Deadline"))) {
            continue;
        }
        else {
            outputTasks(data,i);
        }

    }
    file.close();

}

// Вывод задач по параметру
void Task::showTasksWithParameter(QString status) {
    ClassFunctions::openForReadFile(file);
    int count = 0;
    QDomNodeList data = readFileXML(file);
    for (int i = 0; i < data.count(); i++) {
        if ((data.at(i).lastChildElement("Status").text() == status) && (!isDeleted(data.at(i).lastChildElement("Deadline")))) {
            outputTasks(data,i);
            count++;
        }
        else {
            continue ;
        }
    }
    if (count == 0) {
        qDebug() << "Tasks with this parameter not found!\n";
        file.close();
        return;
    }
    file.close();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Вывод задачи в консоль
void Task::outputTasks(QDomNodeList &data, int id) {
    qDebug() << "Id: " << data.at(id).attributes().namedItem("id").nodeValue().toInt();
    qDebug() << "Caption: " << data.at(id).lastChildElement("Caption").text();
    qDebug() << "Description: " << data.at(id).lastChildElement("Description").text();
    qDebug() << "Priority: " << data.at(id).lastChildElement("Priority").text().toInt();
    qDebug() << "Deadline: " << data.at(id).lastChildElement("Deadline").text();
    qDebug() << "Status: " << data.at(id).lastChildElement("Status").text();
    qDebug() << "Complete: " << (data.at(id).lastChildElement("Complete").text() = "" ?  data.at(id).lastChildElement("Complete").text() : "-");
    qDebug() << "\n";

}

// Считывание XML-файла в объект QDomDocument
QDomNodeList Task::readFileXML(QFile &file) {
    QDomDocument doc;
    doc.setContent(&file);
    QDomNodeList data = doc.elementsByTagName("Task");

    return data;
}

// Изменение данных в определенном тэге
void Task::changeData(int id, QString tagName, QString newTagValue, QDomDocument &doc) {
    if (newTagValue == "-") {
        return;
    }
    if (tagName == "Priority") {
        if (!ClassFunctions::checkPriorityOnValid(newTagValue)) {
            changeData(id,"Priority",ClassFunctions::inputUserData("Priority"),doc);
            return;
        }
    }
    if (tagName == "Deadline") {
        if (!ClassFunctions::checkDeadlineOnValid(newTagValue)) {
            changeData(id,"Deadline",ClassFunctions::inputUserData("Deadline"),doc);
            return;
        }
    }
    QDomNodeList data = doc.elementsByTagName("Task");
    int idTask = findTaskWithId(id, data);
    data.at(idTask).replaceChild(createElement(tagName,newTagValue,doc),data.at(idTask).lastChildElement(tagName));
}

// Поиск определенной задачи по id
int Task::findTaskWithId(int inputId, QDomNodeList &data) {
    for (int i = 0; i < data.count(); ++i) {
        if (QString::number(inputId) == data.at(i).attributes().namedItem("id").nodeValue()) {
            return i;
        }
    }
    return 0;
}

// Проверка, удалена ли задача
bool Task::isDeleted(QDomElement el) {
    if (el.text() == "deleted") {
        return true;
    }
    return false;
}

// Создать тэг с данными
QDomElement Task::createElement (QString tag, QString tagValue, QDomDocument &doc) {
    QDomElement el = doc.createElement(tag);
    el.appendChild(doc.createTextNode(tagValue));

    return el;
}

// Вернуть все данные одной задачи
void Task::getAllData(QVector <QString> &v) {
    v.push_back(getCaption());
    v.push_back(getDescription());
    v.push_back(QString::number(getPriority()));
    v.push_back(getDeadline());
    v.push_back(getStatus());
}
// Перезаписать XML-файл
void Task::saveDoc(QDomDocument &doc) {
    ClassFunctions::openForWriteFile(file);
    file.resize(0);
    QTextStream out(&file);
    doc.save(out,4);
    qDebug() << "Successful!";
    file.close();
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
