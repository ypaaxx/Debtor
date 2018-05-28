#include "mainwindow.h"
#include <QApplication>

#include <debtor.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    auto debtor = new Debtor();
    QObject::connect(debtor, SIGNAL(newCreditorsList(QList<Creditor*>*)), &w, SLOT(setCreditors(QList<Creditor*>*)));
    QObject::connect(&w, SIGNAL(operation(Creditor*,int)), debtor, SLOT(give(Creditor*,int)));

    //Кнопки авторизации
    QObject::connect(&w, SIGNAL(pressAuthorization(QString, QString)), debtor, SLOT(authorization(QString, QString)));



    w.show();
    return a.exec();
}
