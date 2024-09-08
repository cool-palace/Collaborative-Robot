#include "include/scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent)
    , line_pen(QBrush(Qt::green),3)
{ }

Scene::~Scene() {
    clear_all();
}

void Scene::init() {
    double z_axis_pos = width()/2;
    double x_axis_length = width();
    double z_axis_length = height();
    scale = z_axis_length / 2;

    // Setting X axis
    auto x_axis = new QGraphicsLineItem();
    axes.append(x_axis);
    x_axis->setLine(0, z_axis_length, x_axis_length, z_axis_length);

    // Setting Z axis
    auto z_axis = new QGraphicsLineItem();
    axes.append(z_axis);
    z_axis->setLine(z_axis_pos, 0, z_axis_pos, z_axis_length + margin);

    // Adding axes
    QPen axis_pen(QBrush(Qt::black),2,Qt::DashDotLine);
    for (auto axis : axes) {
        axis->setPen(axis_pen);
        addItem(axis);
    }

    // Setting marks
    auto x_1_mark = new QGraphicsLineItem();
    marks.append(x_1_mark);
    x_1_mark->setLine(z_axis_pos + scale, z_axis_length - margin/2, z_axis_pos + scale, z_axis_length + margin/2);

    auto x_minus_1_mark = new QGraphicsLineItem();
    marks.append(x_minus_1_mark);
    x_minus_1_mark->setLine(z_axis_pos - scale, z_axis_length - margin/2, z_axis_pos - scale, z_axis_length + margin/2);

    auto z_1_mark = new QGraphicsLineItem();
    marks.append(z_1_mark);
    z_1_mark->setLine(z_axis_pos - margin/2, z_axis_length - scale, z_axis_pos + margin/2, z_axis_length - scale);

    // Adding marks
    for (auto mark : marks) {
        addItem(mark);
    }

    // Setting labels
    auto x_label = new QGraphicsTextItem("x");
    labels.append(x_label);
    x_label->setPos(x_axis->line().p2() + x_axis_label_offset);

    auto z_label = new QGraphicsTextItem("z");
    labels.append(z_label);
    z_label->setPos(z_axis->line().p1() + z_axis_label_offset);

    auto origin_label = new QGraphicsTextItem("0");
    labels.append(origin_label);
    origin_label->setPos(z_axis->line().p2() + QPointF(5,-10));

    auto x_1_label = new QGraphicsTextItem("1");
    labels.append(x_1_label);
    x_1_label->setPos(x_1_mark->line().p2() + x_axis_label_offset);

    auto x_minus_1_label = new QGraphicsTextItem("-1");
    labels.append(x_minus_1_label);
    x_minus_1_label->setPos(x_minus_1_mark->line().p2() + x_axis_label_offset);

    auto z_1_label = new QGraphicsTextItem("1");
    labels.append(z_1_label);
    z_1_label->setPos(z_1_mark->line().p2() + QPointF(5,-10));

    // Adding labels
    for (auto label : labels) {
        addItem(label);
    }
}

void Scene::clear_lines() {
    for (auto line : lines) {
        delete line;
    }
    lines.clear();
}

void Scene::clear_all() {
    clear_lines();
    for (auto axis : axes) {
        delete axis;
    }
    for (auto mark : marks) {
        delete mark;
    }
    for (auto label : labels) {
        delete label;
    }
}

void Scene::draw_lines(const QList<Point> & points, int rotation_angle) {
    clear_lines();
    double phi = qDegreesToRadians(static_cast<double>(rotation_angle));
    for (int i = 0; i < points.size() - 1; ++i) {
        QLineF line = QLineF((points[i].x()*qCos(phi) - points[i].y()*qSin(phi)) * scale + width()/2, height() - points[i].z() * scale,
                             (points[i+1].x()*qCos(phi) - points[i+1].y()*qSin(phi)) * scale + width()/2, height() - points[i+1].z() * scale);
        lines.push_back(new QGraphicsLineItem(line));
        lines.back()->setPen(line_pen);
        addItem(lines.back());
    }
}
