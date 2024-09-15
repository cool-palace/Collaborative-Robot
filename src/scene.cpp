#include "include/scene.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent)
    , line_pen(QBrush(Qt::darkGreen),3)
{
    axes_points.append(qMakePair(Point(-2,0,0), Point(2,0,0)));
    axes_points.append(qMakePair(Point(0,-2,0), Point(0,2,0)));
    axes_points.append(qMakePair(Point(0,0,-0.1), Point(0,0,2)));
    marks_points.append(qMakePair(Point(-1,0,0.05), Point(-1,0,-0.05)));
    marks_points.append(qMakePair(Point(0,-1,0.05), Point(0,-1,-0.05)));
    marks_points.append(qMakePair(Point(-0.05,0,1), Point(0.05,0,1)));
    marks_points.append(qMakePair(Point(0,1,0.05), Point(0,1,-0.05)));
    marks_points.append(qMakePair(Point(1,0,0.05), Point(1,0,-0.05)));
}

Scene::~Scene() {
    clear_all();
}

void Scene::init() {
    double z_axis_pos = width()/2;
//    double x_axis_length = width();
    double z_axis_length = height();
    scale = z_axis_length / 2;

    // Setting X axis
    auto x_axis = new QGraphicsLineItem();
    axes.append(x_axis);

    // Setting Y axis
    auto y_axis = new QGraphicsLineItem();
    axes.append(y_axis);

    // Setting Z axis
    auto z_axis = new QGraphicsLineItem();
    axes.append(z_axis);
    z_axis->setLine(z_axis_pos, 0, z_axis_pos, z_axis_length + margin);

    // Adding axes
    QPen axis_pen(QBrush(Qt::black),2,Qt::DashDotLine);
    for (int i = 0; i < axes.size(); ++i) {
        Qt::GlobalColor color = i == 0 ? Qt::red : i == 1 ? Qt::blue : Qt::green;
        axis_pen.setColor(color);
        auto axis = axes[i];
        axis->setPen(axis_pen);
        addItem(axis);
    }

    // Setting marks
    auto x_minus_1_mark = new QGraphicsLineItem();
    marks.append(x_minus_1_mark);

    auto y_minus_1_mark = new QGraphicsLineItem();
    marks.append(y_minus_1_mark);

    auto z_1_mark = new QGraphicsLineItem();
    marks.append(z_1_mark);

    auto x_1_mark = new QGraphicsLineItem();
    marks.append(x_1_mark);

    auto y_1_mark = new QGraphicsLineItem();
    marks.append(y_1_mark);

    // Adding marks
    for (auto mark : marks) {
        addItem(mark);
    }

    // Setting labels
    auto x_label = new QGraphicsTextItem("x");
    labels.append(x_label);

    auto y_label = new QGraphicsTextItem("y");
    labels.append(y_label);

    auto z_label = new QGraphicsTextItem("z");
    labels.append(z_label);

    auto origin_label = new QGraphicsTextItem("0");
    labels.append(origin_label);
    origin_label->setPos(z_axis->line().p2() + QPointF(5,-85));

    auto x_minus_1_label = new QGraphicsTextItem("-1");
    marks_labels.append(x_minus_1_label);

    auto y_minus_1_label = new QGraphicsTextItem("-1");
    marks_labels.append(y_minus_1_label);

    auto z_1_label = new QGraphicsTextItem("1");
    marks_labels.append(z_1_label);

    auto y_1_label = new QGraphicsTextItem("1");
    marks_labels.append(y_1_label);

    auto x_1_label = new QGraphicsTextItem("1");
    marks_labels.append(x_1_label);

    // Adding labels
    for (auto label : labels) {
        addItem(label);
    }
    for (auto label : marks_labels) {
        addItem(label);
    }
    draw_axes();
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
    for (auto label : marks_labels) {
        delete label;
    }
}

QLineF Scene::get_line(double x1, double z1, double x2, double z2) {
    return QLineF(x1 * scale + width() / 2, height() - 75 - z1 * scale,
                  x2 * scale + width() / 2, height() - 75 - z2 * scale);
}

void Scene::draw_lines(const QList<Point> & points, int rotation_angle_x, int rotation_angle_y, int rotation_angle_z) {
    clear_lines();
    Matrix m(rotation_angle_x, rotation_angle_y, rotation_angle_z);
    for (int i = 0; i < points.size() - 1; ++i) {
        Point start = m*points[i];
        Point end = m*points[i+1];
        double x1 = start.x(), z1 = start.z();
        double x2 = end.x(), z2 = end.z();
        lines.push_back(new QGraphicsLineItem(get_line(x1, z1, x2, z2)));
        lines.back()->setPen(line_pen);
        addItem(lines.back());
    }
}

void Scene::draw_axes(int rotation_angle_x, int rotation_angle_y, int rotation_angle_z) {
    Matrix m(rotation_angle_x, rotation_angle_y, rotation_angle_z);
    for (int i = 0; i < axes_points.size(); ++i) {
        Point start = m*axes_points[i].first;
        Point end = m*axes_points[i].second;
        double x1 = start.x(), z1 = start.z();
        double x2 = end.x(), z2 = end.z();
        QLineF line = get_line(x1, z1, x2, z2);
        axes[i]->setLine(line);
        labels[i]->setPos(line.p2() + (i == 2 ? z_axis_label_offset : x_axis_label_offset));
        if (line.length() > 30) {
            labels[i]->show();
            marks[i]->show();
            marks_labels[i]->show();
            marks_labels[marks_labels.size() - i - 1]->show();
        } else {
            labels[i]->hide();
            marks[i]->hide();
            marks_labels[i]->hide();
            marks_labels[marks_labels.size() - i - 1]->hide();
        }
    }
    for (int i = 0; i < marks_points.size(); ++i) {
        Point start = m*marks_points[i].first;
        Point end = m*marks_points[i].second;
        double x1 = start.x(), z1 = start.z();
        double x2 = end.x(), z2 = end.z();
        QLineF line = get_line(x1, z1, x2, z2);
        marks[i]->setLine(line);
        marks_labels[i]->setPos(line.p2() + x_axis_label_offset);
    }
}
