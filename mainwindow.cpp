#include "mainwindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Авторизация
    autorization();
}

MainWindow::~MainWindow()
{

}

void MainWindow::autorization(){

    QWidget *window = new QWidget();
    QVBoxLayout* centralLayout = new QVBoxLayout(window);
    window->setLayout(centralLayout);

    QPushButton* button = new QPushButton("YEAH!", window);
    connect(button, SIGNAL(clicked(bool)), this, SLOT(pressOk()));
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

void MainWindow::pressOk() {
    auto text = new QLabel("списки вся хуйня");
    setCentralWidget(text);
}
