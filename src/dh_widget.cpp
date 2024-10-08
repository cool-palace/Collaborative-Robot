#include "include/dh_widget.h"

DH_Widget::DH_Widget(const QString& title, QWidget* parent) : QGroupBox(title, parent) {
    QHBoxLayout* layout = new QHBoxLayout(this);

    // Theta parameter
    QLabel* label_theta = new QLabel("θ: ", this);
    label_theta->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(label_theta);
    theta = new QSpinBox(this);
    theta->setMinimum(-180);
    theta->setMaximum(180);
    theta->setSingleStep(5);
    theta->setSuffix("°");
    layout->addWidget(theta);

    // A parameter
    QLabel* label_a = new QLabel("a: ", this);
    label_a->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(label_a);
    a = new QDoubleSpinBox(this);
    a->setMinimum(-1);
    a->setMaximum(1);
    a->setSingleStep(0.05);
    a->setSuffix(" м");
    layout->addWidget(a);

    // D parameter
    QLabel* label_d = new QLabel("d: ", this);
    label_d->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(label_d);
    d = new QDoubleSpinBox(this);
    d->setMinimum(-1);
    d->setMaximum(1);
    d->setSingleStep(0.05);
    d->setDecimals(3);
    d->setSuffix(" м");
    layout->addWidget(d);

    // Alpha parameter
    QLabel* label_alpha = new QLabel("α: ", this);
    label_alpha->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(label_alpha);
    alpha = new QSpinBox(this);
    alpha->setMinimum(-180);
    alpha->setMaximum(180);
    alpha->setSingleStep(90);
    alpha->setSuffix("°");
    layout->addWidget(alpha);

    setLayout(layout);

    connect(theta, QOverload<int>::of(&QSpinBox::valueChanged), this, &DH_Widget::value_changed);
    connect(a, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DH_Widget::value_changed);
    connect(d, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DH_Widget::value_changed);
    connect(alpha, QOverload<int>::of(&QSpinBox::valueChanged), this, &DH_Widget::value_changed);
}

DH_Widget::~DH_Widget() {
    delete theta;
    delete alpha;
    delete a;
    delete d;
}

QJsonObject DH_Widget::to_json() const {
    QJsonObject result;
    result["theta"] = theta->value();
    result["a"] = a->value();
    result["d"] = d->value();
    result["alpha"] = alpha->value();
    return result;
}
