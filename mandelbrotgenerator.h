#ifndef MANDELBROTGENERATOR_H
#define MANDELBROTGENERATOR_H

#include <QThread>
#include <QSize>

class Matrix;

class MandelbrotGenerator : public QThread
{
public:
    MandelbrotGenerator(QSize size, double xCenter, double yCenter, double range);
    void run();
    Matrix* getResult();
private:
    QSize size;
    double xOffset, yOffset, xDelta, yDelta;
    Matrix *result;
};

#endif // MANDELBROTGENERATOR_H
