#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include "dh_matrix.h"

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
    void clear();
    void draw_lines(const QList<Point>&, int rotation_angle = 0);
    void set_yoz(bool enable) { x_label->setPlainText(enable ? "y" : "x"); }

private:
    double scale;
    QPen line_pen;
    QGraphicsLineItem * x_axis;
    QGraphicsLineItem * z_axis;
    QGraphicsTextItem * x_label;
    QGraphicsTextItem * z_label;
    QGraphicsLineItem * x_1_mark;
    QGraphicsLineItem * x_minus_1_mark;
    QGraphicsLineItem * z_1_mark;
    QGraphicsTextItem * x_1_label;
    QGraphicsTextItem * x_minus_1_label;
    QGraphicsTextItem * z_1_label;
    QGraphicsTextItem * origin_label;
    QList<QGraphicsLineItem*> lines;
};

#endif // SCENE_H
