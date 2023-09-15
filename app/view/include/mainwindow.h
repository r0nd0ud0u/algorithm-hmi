#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "pathfinderpanel.h"

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

    class MainWindow : public QMainWindow
{
    Q_OBJECT

        public:
                 MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void ActivateGridGame(algo& curAlgo);
    void SetWidth(int width);
    void SetHeight(int height);
    void SetModeEdit();
    void SetModeWork();

};
#endif // MAINWINDOW_H
