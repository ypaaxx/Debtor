#ifndef DEBTOR_H
#define DEBTOR_H

#include "creditor.h"

#include <QBitArray>
#include <QObject>
#include <QTcpSocket>

class Debtor : public QObject
{
    Q_OBJECT
private:
    int const PORT = 48654;
    QString const host = "localhost";
    enum COMMAND{AUTH, BLNC, OPRT};
    QList<Creditor *> *creditors;
    QTcpSocket* socket;
    QDataStream stream;
public:
    explicit Debtor(QObject *parent = nullptr);

    /* Получаем от сервера список известных имен */
    void getCreditors(){
        int size=0; // Количество кредиторов
        stream >> size;
        if (!size) return; // Раз так, то отключаемся
        creditors = new QList <Creditor *>;

        while (size--){
            QString name;
            int balance;
            stream >> name;
            stream >> balance;
            for (Creditor* creditor: *creditors){
                if(name == creditor->getName()){
                    creditor->setBalance(balance);
                    break;
                }
            }
            creditors->append(new Creditor(name, balance));
            qDebug() << name << balance;
        }
        emit newCreditorsList(creditors); // Сообщаем всем о обновлении списка
    }
    QList<Creditor *>* getList(){return creditors;}

public slots:
    /* Авторизируемся на сервере по логину и паролю
     * При удачной авторизации остаётся соединение с сервером и возращается тря */
    void authorization(QString login, QString password){
        // Send login and pass to server. If evrithing is OK server dont disconect the socket
        socket = new QTcpSocket;
        qDebug() << "Попытка связаться с сервером";
        socket->connectToHost(host, PORT);
        if (socket->waitForConnected(5000)){
        qDebug() << "Соединение установленно"; //Это не так, но пусть будет так

        connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
        stream.setDevice(socket);
        stream << 0; // флаг авторизации
        stream << login;
        stream << password;

        qDebug() << 0 << login << password;
        }else{
            qDebug() << "Таймаут соединения с сервером";
        }
    }

    /* Срабатывает на ReadyRead и распределяет что там пришло */
    void read(){
        char command = 0;
        int* p;
        socket->getChar(&command);
        //stream >> command;
        qDebug() << "incoming command" << command;

        switch (command) {
        case AUTH:
            getCreditors();
            break;
        case BLNC:
            getCreditors();
            break;
        case OPRT:

        default:
            break;
        }
    }

    /* Отдолжить персоне денег
     * При взятии знак минус  */
    void give(Creditor *person, int sum){
        stream << OPRT;
        stream << person->getName() << sum;
        qDebug() << person->getName() << sum;
    }
signals:
    void newCreditorsList(QList <Creditor *> *);
};

#endif // DEBTOR_H
