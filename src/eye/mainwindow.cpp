#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "eye.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(new Eye(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}
