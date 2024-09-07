#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include "dh_widget.h"
#include "scene.h"

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
    Scene* scene;
    QList<DH_Widget*> dh_widgets;
    void calculate();

    void save_settings() const;
    void load_settings();
};
#endif // MAINWINDOW_H
