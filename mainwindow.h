#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <creditor.h>

class MainWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QList<Creditor *> *creditors = NULL;
    QVBoxLayout *layoutCreditors;

private:
    void autorizationPage();

    class AuthWidget: public QWidget{
        QPushButton *button;
        QLineEdit* login;
        QLineEdit* password;
    public:
        AuthWidget() : QWidget(){

            QVBoxLayout* centralLayout = new QVBoxLayout(this);
            setLayout(centralLayout);

            button = new QPushButton("YEAH!", this);
            //connect(button, &QPushButton::clicked, this, &AuthWidget::pressOk);
            login = new QLineEdit(this);

            login->setPlaceholderText("LOGIN");
            password = new QLineEdit(this);
            password->setPlaceholderText("PASSWORD");
            password->setEchoMode(QLineEdit::Password);

            centralLayout->addStretch();
            centralLayout->addWidget(login);
            centralLayout->addWidget(password);
            centralLayout->addWidget(button);
            centralLayout->addStretch();
        }
    //public slots:
        void pressOk(){
            //emit MainWindow::pressAuthorization(login->text(), password->text());
            //emit auth(login->text(), password->text());
        }
    //signals:
        //void auth(QString, QString);
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void setCreditors(QList<Creditor *> *_creditors);

signals:
    void pressAuthorization(QString, QString);
    void operation(Creditor*, int);
private slots:
    void pressAuth();
    void giveWindow(Creditor *creditor);
    void pressGive(Creditor *creditor, int sum);

};

#endif // MAINWINDOW_H
