#ifndef DH_WIDGET_H
#define DH_WIDGET_H

#include <QObject>
#include <QGroupBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QJsonObject>
#include <dh_matrix.h>

class DH_Widget : public QGroupBox
{
    Q_OBJECT
public:
    explicit DH_Widget(const QString&, QWidget *parent = nullptr);

signals:
    void value_changed();

public slots:
    DH_Matrix matrix() const { return DH_Matrix(theta->value(), a->value(), d->value(), alpha->value()); }
    QJsonObject to_json() const;
    void set_theta(int value) { theta->setValue(value); }
    void set_alpha(int value) { alpha->setValue(value); }
    void set_a(double value) { a->setValue(value); }
    void set_d(double value) { d->setValue(value); }
    int get_theta() { return theta->value(); }
    int get_alpha() { return alpha->value(); }
    double get_a() { return a->value(); }
    double get_d() { return d->value(); }

private:
    QSpinBox* theta;
    QSpinBox* alpha;
    QDoubleSpinBox* a;
    QDoubleSpinBox* d;

};

#endif // DH_WIDGET_H
