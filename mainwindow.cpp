#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new Scene())
{
    ui->setupUi(this);
    ui->view->setScene(scene);
    scene->setSceneRect(0,0,ui->view->width()-margin, ui->view->height());
    scene->init();

    connect(ui->load, &QAction::triggered, this, &MainWindow::load_settings);
    connect(ui->save, &QAction::triggered, this, &MainWindow::save_settings);

    for (int i = 0; i < 6; ++i) {
        dh_widgets.push_back(new DH_Widget(QString("Узел %1").arg(i+1)));
        connect(dh_widgets.back(), &DH_Widget::value_changed, this, &MainWindow::calculate);
        ui->verticalLayout->addWidget(dh_widgets.back());
    }
    connect(ui->calculate, &QPushButton::clicked, this, &MainWindow::calculate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate() {
    QList<Point> points;
    points.append(Point());
//    qDebug() << "Calculating: ";
    DH_Matrix result = dh_widgets.first()->matrix();
    points.append(result.coordinates());
    for (int i = 1; i < 6; ++i) {
        result *= dh_widgets[i]->matrix();
        points.append(result.coordinates());
//        qDebug() << QString("Step %1").arg(i) << result;
    }
    scene->draw_lines(points);
    auto p = points.back();
    ui->statusbar->showMessage(QString("Координаты положения последнего сочленения: "
                                       "x: %1, y: %2, z: %3").arg(p.x()).arg(p.y()).arg(p.z()));
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
        disconnect(current, nullptr, nullptr, nullptr);
        current->set_theta(joint["theta"].toInt(current->get_theta()));
        current->set_alpha(joint["alpha"].toInt(current->get_alpha()));
        current->set_a(joint["a"].toDouble(current->get_a()));
        current->set_d(joint["d"].toDouble(current->get_d()));
        connect(current, &DH_Widget::value_changed, this, &MainWindow::calculate);
    }
    ui->statusbar->showMessage("Настройки загружены");
}
