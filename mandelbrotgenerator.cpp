#include "mandelbrotgenerator.h"
#include "basicmandelbrotcalculator.h"
#include "matrix.h"

#define ITERATIONS 256.0

MandelbrotGenerator::MandelbrotGenerator(QSize size, double xCenter, double yCenter, double range) :
        size(size),
        xOffset(xCenter - range/2.0),
        yOffset(yCenter + range/2.0),
        xDelta(range/double(size.width())),
        yDelta(-1.0*range/double(size.height()))
{
}

void MandelbrotGenerator::run()
{
    MandelbrotCalculator *mc = new BasicMandelbrotCalculator();
    result = new Matrix(size.width(), size.height());
    for (int x=0; x<size.width(); x++)
    {
        for (int y=0; y<size.height(); y++)
        {
            result->set(x, y, mc->getDepth(complex(xOffset+xDelta*x, yOffset+yDelta*y), ITERATIONS)/ITERATIONS);
        }
    }
}

Matrix *MandelbrotGenerator::getResult()
{
    return result;
}
