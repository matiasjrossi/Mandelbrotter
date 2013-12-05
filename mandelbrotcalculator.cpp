#include "mandelbrotcalculator.h"
#include "logger.h"

double MandelbrotCalculator::getDepth(complex point, unsigned long maxIterations) const
{
    if (point.real() < -2.0 || point.real() > 1.0)
        Logger::get()->debug(QString("MandelbrotCalculator::getDepth [Out of boundary real value %1]").arg(point.real()));
    if (point.imag() < -1.0 || point.imag() > 1.0)
        Logger::get()->debug(QString("MandelbrotCalculator::getDepth [Out of boundary imaginary value %1]").arg(point.imag()));
    return performCalculation(point, maxIterations);
}
