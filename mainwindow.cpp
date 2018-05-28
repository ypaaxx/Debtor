#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Авторизация
    autorizationPage();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setCreditors(QList<Creditor *> *_creditors) {
    creditors = _creditors;
    delete layoutCreditors; //Удаляем прошлый список

    layoutCreditors = new QVBoxLayout;
    layoutCreditors->addWidget(new QLabel("+ вы должны"
                                          "- вам"));
    for(Creditor *person: *creditors){//
        layoutCreditors->addLayout(person->getLayout());
        connect(person, SIGNAL(toSend(Creditor*,int)), this, SLOT(pressGive(Creditor*,int)));
    }
    layoutCreditors->addStretch();
    QWidget* w = new QWidget;
    w->setLayout(layoutCreditors);
    setCentralWidget(w);
}

void MainWindow::autorizationPage(){
    //AuthWidget *authW = new AuthWidget;
    QWidget *window = new QWidget();
    QVBoxLayout* centralLayout = new QVBoxLayout(window);
    window->setLayout(centralLayout);

    QPushButton* button = new QPushButton("YEAH!", window);
    connect(button, SIGNAL(clicked(bool)), this, SLOT(pressAuth()));
    QLineEdit* login = new QLineEdit(window);
    login->setPlaceholderText("LOGIN");
    QLineEdit* password = new QLineEdit(window);
    password->setPlaceholderText("PASSWORD");
    password->setEchoMode(QLineEdit::Password);

    centralLayout->addStretch();
    centralLayout->addWidget(login);
    centralLayout->addWidget(password);
    centralLayout->addWidget(button);
    centralLayout->addStretch();

    setCentralWidget(window);
}

void MainWindow::pressAuth() {

    emit pressAuthorization("fura", "132435");

    layoutCreditors = new QVBoxLayout;
    layoutCreditors->addWidget(new QLabel("подождём"));
    layoutCreditors->addStretch();
    QWidget* w = new QWidget;
    w->setLayout(layoutCreditors);
    setCentralWidget(w);
}

void MainWindow::giveWindow(Creditor *creditor){
    QWidget *window = new QWidget;
    auto layout = new QVBoxLayout(window);
    layout->addWidget(new QLabel( "Новое окно " + creditor->getName(),window ));
    layout->addWidget(new QSpinBox(window));
    QPushButton* button = new QPushButton("give",window);

    connect(button, SIGNAL(clicked(bool)), this, SLOT(pressGive(Creditor*,int)));
    connect(button, SIGNAL(clicked(bool)), window, SLOT(deleteLater()));
    layout->addWidget(button);

    window->setLayout(layout);
    window->show();
    window->activateWindow();
}

void MainWindow::pressGive(Creditor *creditor, int sum)
{
    emit operation(creditor, sum);
}
