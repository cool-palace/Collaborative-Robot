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
    void draw_lines(const QList<Point>&, int rotation_angle = 0);
    void set_yoz(bool enable) { labels.first()->setPlainText(enable ? "y" : "x"); }

private:
    void clear_lines();
    void clear_all();
    double scale;
    QPen line_pen;
    QList<QGraphicsLineItem*> axes;
    QList<QGraphicsLineItem*> marks;
    QList<QGraphicsTextItem*> labels;
    QList<QGraphicsLineItem*> lines;
};

#endif // SCENE_H
