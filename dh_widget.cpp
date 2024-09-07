#include "dh_widget.h"

DH_Widget::DH_Widget(const QString& title, QWidget* parent) : QGroupBox(title, parent) {
    QHBoxLayout* layout = new QHBoxLayout(this);

    QLabel* label_theta = new QLabel("θ: ", this);
    label_theta->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(label_theta);
    theta = new QSpinBox(this);
    theta->setMinimum(-180);
    theta->setMaximum(180);
    theta->setSuffix("°");
    layout->addWidget(theta);

    QLabel* label_a = new QLabel("a: ", this);
    label_a->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(label_a);
    a = new QDoubleSpinBox(this);
    a->setMinimum(-1);
    a->setMaximum(1);
    a->setSingleStep(0.05);
    a->setSuffix(" м");
    layout->addWidget(a);

    QLabel* label_d = new QLabel("d: ", this);
    label_d->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(label_d);
    d = new QDoubleSpinBox(this);
    d->setMinimum(-1);
    d->setMaximum(1);
    d->setSingleStep(0.05);
    d->setSuffix(" м");
    layout->addWidget(d);

    QLabel* label_alpha = new QLabel("α: ", this);
    label_alpha->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(label_alpha);
    alpha = new QSpinBox(this);
    alpha->setMinimum(-180);
    alpha->setMaximum(180);
    alpha->setSuffix("°");
    layout->addWidget(alpha);

    setLayout(layout);
}
