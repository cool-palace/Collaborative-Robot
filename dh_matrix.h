#ifndef DH_MATRIX_H
#define DH_MATRIX_H
#include <QtMath>
#include <QDebug>

class Point {
private:
    double x_, y_, z_;

public:
    Point(double x = 0, double y = 0, double z = 0) : x_(x), y_(y), z_(z) {}
    double x() const { return x_; }
    double y() const { return y_; }
    double z() const { return z_; }
};

class DH_Matrix
{
private:
    double matrix[4][4];

public:
    DH_Matrix(int theta = 0, double a = 0, double d = 0, int alpha = 0);
    DH_Matrix operator*(const DH_Matrix& other) const;
    Point coordinates() const { return Point(matrix[0][3], matrix[1][3], matrix[2][3]); }
    friend QDebug& operator<<(QDebug debug, const DH_Matrix& m);
};

#endif // DH_MATRIX_H
