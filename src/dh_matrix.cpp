#include "include/dh_matrix.h"

QDebug& operator<<(QDebug debug, const Point& p) {
    debug << "Point (" << QString::number(p.x_, 'f', 6).toUtf8().constData() << ", "
                       << QString::number(p.y_, 'f', 6).toUtf8().constData() << ", "
                       << QString::number(p.z_, 'f', 6).toUtf8().constData() << ")\n";
    return debug.noquote();
}

DH_Matrix::DH_Matrix(int theta_, double a, double d, int alpha_) {
    double theta = qDegreesToRadians(static_cast<double>(theta_));
    double alpha = qDegreesToRadians(static_cast<double>(alpha_));

    matrix[0][0] = qCos(theta);
    matrix[0][1] = -qSin(theta) * qCos(alpha);
    matrix[0][2] = qSin(theta) * qSin(alpha);
    matrix[0][3] = a * qCos(theta);

    matrix[1][0] = qSin(theta);
    matrix[1][1] = qCos(theta) * qCos(alpha);
    matrix[1][2] = -qCos(theta) * qSin(alpha);
    matrix[1][3] = a * qSin(theta);

    matrix[2][0] = 0;
    matrix[2][1] = qSin(alpha);
    matrix[2][2] = qCos(alpha);
    matrix[2][3] = d;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;
}

DH_Matrix DH_Matrix::operator*(const DH_Matrix &other) const {
    DH_Matrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.matrix[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
            }
        }
    }
    return result;
}

DH_Matrix &DH_Matrix::operator*=(const DH_Matrix &other) {
    auto result = (*this) * other;
    std::memcpy(matrix, result.matrix, 4 * 4 * sizeof(double));
    return *this;
}

QDebug& operator<<(QDebug debug, const DH_Matrix& m) {
    debug.nospace() << "DH_Matrix(";
    for (int i = 0; i < 4; ++i) {
        debug.nospace() << "\n[ ";
        for (int j = 0; j < 4; ++j) {
            debug.nospace() << QString::number(m.matrix[i][j], 'f', 5).rightJustified(9).toUtf8().constData() << " ";
        }
        debug.nospace() << "]";
    }
    debug.nospace() << "\n)";
    return debug.space();
}

Matrix::Matrix(int alpha_, int beta_, int gamma_) {
    double alpha = qDegreesToRadians(static_cast<double>(alpha_));
    double beta = qDegreesToRadians(static_cast<double>(beta_));
    double gamma = qDegreesToRadians(static_cast<double>(gamma_));
    // Angles alpha, beta, gamma represent rotation around X, Y and Z axes respectively
    matrix[0][0] = qCos(gamma)*qCos(beta) - qSin(gamma)*qSin(alpha)*qSin(beta);
    matrix[0][1] = -qSin(gamma)*qCos(beta) - qCos(gamma)*qSin(alpha)*qSin(beta);
    matrix[0][2] = -qCos(alpha)*qSin(beta);
    matrix[1][0] = qSin(gamma)*qCos(alpha);
    matrix[1][1] = qCos(gamma)*qCos(alpha);
    matrix[1][2] = -qSin(alpha);
    matrix[2][0] = qSin(gamma)*qSin(alpha)*qCos(beta) + qCos(gamma)*qSin(beta);
    matrix[2][1] = qCos(gamma)*qSin(alpha)*qCos(beta) - qSin(gamma)*qSin(beta);
    matrix[2][2] = qCos(alpha)*qCos(beta);
}

Point Matrix::operator* (const Point& p) {
    qreal x = p.x()*matrix[0][0] + p.y()*matrix[0][1] + p.z()*matrix[0][2];
    qreal y = p.x()*matrix[1][0] + p.y()*matrix[1][1] + p.z()*matrix[1][2];
    qreal z = p.x()*matrix[2][0] + p.y()*matrix[2][1] + p.z()*matrix[2][2];
    return Point(x, y, z);
}
