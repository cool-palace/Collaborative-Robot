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

private:
    double scale;
    QPen line_pen;
    QGraphicsLineItem * x_axis;
    QGraphicsLineItem * z_axis;
    QGraphicsTextItem * x_label;
    QGraphicsTextItem * z_label;
    QGraphicsTextItem * origin_label;
    QList<QGraphicsLineItem*> lines;
};

#endif // SCENE_H
