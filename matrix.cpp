#include "matrix.h"

Matrix::Matrix(unsigned width, unsigned height) :
        width(width),
        height(height),
        data(new double[width*height])
{
}

Matrix::Matrix(Matrix &other) :
        width(other.width),
        height(other.height),
        data(new double[width*height])
{
    for (int i=0; i<width; i++)
        for (int j=0; j<height; j++)
            set(i,j,other.get(i,j));
}

Matrix::Matrix(Matrix *other) :
        width(other->width),
        height(other->height),
        data(new double[width*height])
{
    for (int i=0; i<width; i++)
        for (int j=0; j<height; j++)
            set(i,j,other->get(i,j));
}

double Matrix::get(unsigned x, unsigned y) const
{
    return this->data[y*width+x];
}

void Matrix::set(unsigned x, unsigned y, double data)
{
    this->data[y*width+x] = data;
}

QSize Matrix::size() const
{
    return QSize(width, height);
}

Matrix::~Matrix()
{
    delete[] this->data;
}
