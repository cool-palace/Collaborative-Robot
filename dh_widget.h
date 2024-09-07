#ifndef DH_WIDGET_H
#define DH_WIDGET_H

#include <QObject>
#include <QGroupBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>

class DH_Widget : public QGroupBox
{
    Q_OBJECT
public:
    explicit DH_Widget(const QString&, QWidget *parent = nullptr);

signals:

private:
    QSpinBox* theta;
    QSpinBox* alpha;
    QDoubleSpinBox* a;
    QDoubleSpinBox* d;

};

#endif // DH_WIDGET_H
