#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->load, &QAction::triggered, this, &MainWindow::load_settings);
    connect(ui->save, &QAction::triggered, this, &MainWindow::save_settings);

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

void MainWindow::save_settings() const {
    QJsonObject settings;
    QJsonArray joints;
    for (const auto item : dh_widgets) {
        joints.append(item->to_json());
    }
    settings["joints"] = joints;

    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Сохранить файл"),
                                                    QCoreApplication::applicationDirPath() + "//untitled.json",
                                                    tr("Файлы настроек (*.json)"));
    if (!fileName.isNull()) {
        QFile file(fileName);
        if (file.open(QFile::WriteOnly | QFile::Truncate)) {
            QTextStream out(&file);
            out << QJsonDocument(settings).toJson();
            file.close();
        }
        ui->statusbar->showMessage("Настройки сохранены");
    }
}

void MainWindow::load_settings() {
    QString filepath = QFileDialog::getOpenFileName(nullptr, "Открыть файл настроек",
                                                    QCoreApplication::applicationDirPath(),
                                                    "Файлы настроек (*.json)");
    QFile file(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject settings = doc.object();
    QJsonArray joints = settings["joints"].toArray();
    if (joints.size() != dh_widgets.size()) {
        ui->statusbar->showMessage("Файл настроек содержит неверное число сочленений.");
        return;
    }
    for (int i = 0; i < joints.size(); ++i) {
        auto joint = joints[i].toObject();
        DH_Widget* current = dh_widgets[i];
        current->set_theta(joint["theta"].toInt(current->get_theta()));
        current->set_alpha(joint["alpha"].toInt(current->get_alpha()));
        current->set_a(joint["a"].toDouble(current->get_a()));
        current->set_d(joint["d"].toDouble(current->get_d()));
    }
    ui->statusbar->showMessage("Настройки загружены");
}
