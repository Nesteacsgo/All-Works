#include "classfunctions.h"
#include "iostream"

#include <QDebug>
#include <QDate>

ClassFunctions::ClassFunctions() {}

QString ClassFunctions::inputId() {
    std::string id;
    std::cout << "Enter id\n";
    std::getline(std::cin,id);
    return QString::fromStdString(id);
}

void ClassFunctions::openForReadFile(QFile &file) {
    if (file.isOpen()) {
        file.close();
    }
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File not open";
        return ;
    }
    else {
        qDebug() << "File opened";
    }
}

void ClassFunctions::openForWriteFile(QFile &file) {
    if (file.isOpen()) {
        file.close();
    }
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "File not open";
        return ;
    }
    else {
        qDebug() << "File opened";
    }
}

QString ClassFunctions::inputUserData(QString tag) {
    std::cout << "Enter the "+tag.toStdString()+" : ";
    std::string  userInput;
    std::getline(std::cin,userInput);
    return QString::fromStdString(userInput);
}



bool ClassFunctions::checkPriorityOnValid(QString num) {
    if (num == "-" || num == "deleted" || (0 < num.toInt() && num.toInt() <= 10)) {
        return true;
    }
    else {
        qDebug() << "Wrong priority, try again!\n";
        return false;
    }
}

bool ClassFunctions::checkDeadlineOnValid(QString date) {
    if (QDate::fromString(date,"dd.MM.yyyy") < QDate::currentDate()) {
        return false;
    }
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

    if (date == "-" || date == "deleted" || (checkDays(QString::fromStdString(dateDays).toInt(),(QString::fromStdString(dateMonth).toInt())) &&
                        checkMonth(QString::fromStdString(dateMonth).toInt()) &&
                        checkYear(QString::fromStdString(dateYear).toInt()))) {
        return true;
    }
    else {
        qDebug() << "Wrong date, try again!";
        return false;
    }
}

bool ClassFunctions::checkDays(int days, int month) {
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

bool ClassFunctions::checkMonth(int month) {
     if (month > 0 && month <= 12) {
        return true;
    }
    else {
        return false;
    }

}

bool ClassFunctions::checkYear(int year) {
    if (year >= QDate::currentDate().toString("yyyy").toInt() && year < 2200) {
        return true;
    }
    else {
        return false;
    }
}
