#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "include/dh_matrix.h"

const double margin = 10;
const QPointF z_axis_label_offset = QPointF(-15,-10);
const QPointF x_axis_label_offset = QPointF(-10,0);

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QObject* parent = nullptr);
    virtual ~Scene();
    void init();
    void draw_lines(const QList<Point>&, int rotation_angle_x = 0, int rotation_angle_y = 0, int rotation_angle_z = 0);
    void draw_axes(int rotation_angle_x = 0, int rotation_angle_y = 0, int rotation_angle_z = 0);

private:
    void clear_lines();
    void clear_all();
    QLineF get_line(const Point&, const Point&);
    double scale;
    QPen line_pen;
    QList<QPair<Point, Point>> axes_points;
    QList<QPair<Point, Point>> marks_points;
    QList<QGraphicsLineItem*> axes;
    QList<QGraphicsLineItem*> marks;
    QList<QGraphicsTextItem*> labels;
    QList<QGraphicsTextItem*> marks_labels;
    QList<QGraphicsLineItem*> lines;
};

#endif // SCENE_H
