#ifndef CREDITOR_H
#define CREDITOR_H

#include <QLabel>
#include <QObject>
#include <QTcpSocket>
#include <QLayout>
#include <QString>
#include <QPushButton>
#include <QSpinBox>

/* Персона которая должа нам денег
 * или мы должны */
class Creditor : public QObject
{
    Q_OBJECT
    QWidget *window;
    QSpinBox *spin;
public:
    explicit Creditor(QObject *parent = nullptr);
    explicit Creditor(QString _name, int _balance, QObject *parent = nullptr){
        name = _name;
        balance = _balance;
    }

    QString getName(){
        return name;
    }
    void setBalance(int _balance){ balance = _balance;}
    /* Часть в списке кредиторов */
    QLayout* getLayout(){
        auto layout = new QHBoxLayout();
        layout->addWidget(new QLabel(name));
        layout->addStretch();
        layout->addWidget(new QLabel(QString::number(balance)));
        auto give = new QPushButton("new operation");
        layout->addWidget(give);
        connect(give, SIGNAL(clicked(bool)), this, SLOT(giveWindow()));
        return layout;
    }
public slots:


    void giveWindow(){
        qDebug() << "Button pushed";
        window = new QWidget;
        auto layout = new QVBoxLayout(window);
        layout->addWidget(new QLabel( "Operation with " + getName(),window ));
        layout->addWidget(spin = new QSpinBox(window));
        QPushButton* button = new QPushButton("give",window);

        connect(button, SIGNAL(clicked(bool)), this, SLOT(pushButtontoSend()));
        layout->addWidget(button);

        window->setLayout(layout);
        window->show();
        window->activateWindow();

    }
    void pushButtontoSend(){
        /* Отправляет кому сколько отдать */
        emit toSend(this, spin->value());
        delete window;
    }
private:
    QString name;
    int balance;
    QWidget* w;
signals:
    void toSend(Creditor*, int);
    void operation(Creditor*); //Вызывается при нажатии кнопки новой операции в списке кредиторов
};

#endif // CREDITOR_H
