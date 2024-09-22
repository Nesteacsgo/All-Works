#ifndef CLASSFUNCTIONS_H
#define CLASSFUNCTIONS_H

#include <QDomDocument>
#include <QFile>

class ClassFunctions
{
public:
    ClassFunctions();

    static QDomNodeList readFileXML(QFile &file);
    static void openForReadFile(QFile &file);
    static void openForWriteFile(QFile &file);
    static void outputTask(QDomNodeList &data, int num);
    static QString inputId();
    static QString inputUserData(QString tag);



    static bool checkPriorityOnValid(QString num);
    static bool checkDeadlineOnValid(QString date);

    static bool checkDays(int days, int month);
    static bool checkMonth(int month);
    static bool checkYear(int year);

    QVector <int> monthsWith31 {1,3,5,7,8,10,12};

};

#endif // CLASSFUNCTIONS_H
