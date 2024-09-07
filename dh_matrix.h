#ifndef DH_MATRIX_H
#define DH_MATRIX_H
#include <QtMath>
#include <QDebug>

class DH_Matrix
{
private:
    double matrix[4][4];

public:
    DH_Matrix(int theta = 0, double a = 0, double d = 0, int alpha = 0);
    DH_Matrix operator*(const DH_Matrix& other) const;
    friend QDebug& operator<<(QDebug debug, const DH_Matrix& m);
};

#endif // DH_MATRIX_H
