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
    connect(ui->calculate, &QPushButton::clicked, this, &MainWindow::calculate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate() const {
    qDebug() << "Calculating: ";
    DH_Matrix result = dh_widgets.first()->matrix();
    for (int i = 1; i < 6; ++i) {
        result = result * dh_widgets[i]->matrix();
        qDebug() << QString("Step %1").arg(i) << result;
    }
}

