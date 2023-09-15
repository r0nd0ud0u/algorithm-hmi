#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pathfinder_panel, &PathFinderPanel::SigAlgoSelected, this, &MainWindow::ActivateGridGame);
    connect(ui->pathfinder_panel, &PathFinderPanel::SigChangeHeight, this, &MainWindow::SetHeight);
    connect(ui->pathfinder_panel, &PathFinderPanel::SigChangeWidth, this, &MainWindow::SetWidth);
    connect(ui->pathfinder_panel, &PathFinderPanel::SigModeEdit, this, &MainWindow::SetModeEdit);
    connect(ui->pathfinder_panel, &PathFinderPanel::SigModeWork, this, &MainWindow::SetModeWork);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ActivateGridGame(algo& curAlgo)
{
    ui->grid_panel->ActivateButtons(curAlgo);
}

void MainWindow::SetWidth(int value)
{
    ui->grid_panel->SetWidth(value);
}

void MainWindow::SetHeight(int value)
{
    ui->grid_panel->SetHeight(value);
}

void MainWindow::SetModeEdit()
{
    ui->grid_panel->SetModeEdit();
}

void MainWindow::SetModeWork()
{
    ui->grid_panel->SetModeWork();
}
