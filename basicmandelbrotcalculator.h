#ifndef BASICMANDELBROTCALCULATOR_H
#define BASICMANDELBROTCALCULATOR_H

#include "mandelbrotcalculator.h"

class BasicMandelbrotCalculator : public MandelbrotCalculator
{
protected:
    double performCalculation(complex point, unsigned long maxIterations) const;
};

#endif // BASICMANDELBROTCALCULATOR_H
