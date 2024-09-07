#ifndef DH_WIDGET_H
#define DH_WIDGET_H

#include <QObject>
#include <QGroupBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <dh_matrix.h>

class DH_Widget : public QGroupBox
{
    Q_OBJECT
public:
    explicit DH_Widget(const QString&, QWidget *parent = nullptr);

public slots:
    void value_changed();

private:
    QSpinBox* theta;
    QSpinBox* alpha;
    QDoubleSpinBox* a;
    QDoubleSpinBox* d;

};

#endif // DH_WIDGET_H
