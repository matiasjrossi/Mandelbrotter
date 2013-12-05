#ifndef MATRIX_H
#define MATRIX_H

#include <QSize>

class Matrix
{
public:
    Matrix(unsigned width, unsigned height);
    Matrix(Matrix &other);
    Matrix(Matrix *other);
    double get(unsigned x, unsigned y) const;
    void set(unsigned x, unsigned y, double data);
    QSize size() const;
    ~Matrix();
private:
    unsigned width;
    unsigned height;
    double *data;
};

#endif // MATRIX_H
