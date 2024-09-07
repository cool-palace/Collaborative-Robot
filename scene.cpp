#include "scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent)
    , line_pen(QBrush(Qt::green),3)
    , x_axis(new QGraphicsLineItem())
    , z_axis(new QGraphicsLineItem())
    , x_label(new QGraphicsTextItem("x"))
    , z_label(new QGraphicsTextItem("z"))
    , origin_label(new QGraphicsTextItem("0"))
{

}

void Scene::init() {
    double z_axis_pos = width()/2;
    double x_axis_length = width();
    double z_axis_length = height();
    scale = z_axis_length / 2;

    // updating axes projection
    z_axis->setLine(z_axis_pos, 0, z_axis_pos, z_axis_length + margin);
    x_axis->setLine(0, z_axis_length, x_axis_length, z_axis_length);
    x_label->setPos(x_axis->line().p2() + x_axis_label_offset);
    z_label->setPos(z_axis->line().p1() + z_axis_label_offset);
    origin_label->setPos(z_axis->line().p2() + QPointF(5,-10));

    QPen axis_pen(QBrush(Qt::black),2,Qt::DashDotLine);
    x_axis->setPen(axis_pen);
    z_axis->setPen(axis_pen);

    addItem(x_axis);
    addItem(z_axis);
    addItem(x_label);
    addItem(z_label);
    addItem(origin_label);
}

void Scene::clear() {
    for (auto line : lines) {
        delete line;
    }
    lines.clear();
}

void Scene::draw_lines(const QList<Point> & points, int rotation_angle) {
    clear();
    double theta = qDegreesToRadians(static_cast<double>(rotation_angle));
    for (int i = 0; i < points.size() - 1; ++i) {
        QLineF line = QLineF((points[i].x()*qCos(theta) - points[i].y()*qSin(theta)) * scale + width()/2, height() - points[i].z() * scale,
                             (points[i+1].x()*qCos(theta) - points[i+1].y()*qSin(theta)) * scale + width()/2, height() - points[i+1].z() * scale);
        lines.push_back(new QGraphicsLineItem(line));
        lines.back()->setPen(line_pen);
        addItem(lines.back());
    }
}
