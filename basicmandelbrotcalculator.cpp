#include "basicmandelbrotcalculator.h"
#include <math.h>
#include <QDebug>

double renormalize(unsigned long escapeCount, double norm)
{
    /* mu = N + 1 - log (log  |Z(N)|) / log 2 */
    return double(escapeCount) + 1 - log2(log2(norm)); //log2(2) = 1
}

double BasicMandelbrotCalculator::performCalculation(complex point, unsigned long maxIterations) const
{
    complex previous(0.0,0.0);
    unsigned long iterations = 0;
    do
    {
        previous = previous.square();
        previous += point;
        if (iterations++ > maxIterations)
            return maxIterations;
    } while (previous.squaredNorm() < 4.0);
    return renormalize(iterations, previous.norm());
}
