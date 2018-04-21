#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

    void autorization();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void pressOk();

};

#endif // MAINWINDOW_H
