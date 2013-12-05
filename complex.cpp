#include "complex.h"

#include <math.h>
#include <cmath>

complex::complex(double real, double imag) :
        std::complex<double>(real, imag)
{
}

complex complex::square() const
{
    return complex(pow(real(), 2)-pow(imag(), 2), 2.0*real()*imag());
}

double complex::squaredNorm() const
{
    return pow(real(), 2)+pow(imag(), 2);
}

double complex::norm() const
{
    return sqrt(squaredNorm());
}
