#ifndef MANDELBROTCALCULATOR_H
#define MANDELBROTCALCULATOR_H

#include "complex.h"

class MandelbrotCalculator
{
public:
    double getDepth(complex point, unsigned long maxIterations) const;
protected:
    virtual double performCalculation(complex point, unsigned long maxIterations) const = 0;
};

#endif // MANDELBROTCALCULATOR_H
