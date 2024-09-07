#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < 6; ++i) {
        dh_widgets.push_back(new DH_Widget(QString("Узел %1").arg(i+1)));
        ui->verticalLayout->addWidget(dh_widgets.back());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

