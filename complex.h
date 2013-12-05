#ifndef COMPLEX_H
#define COMPLEX_H

#include <complex>

class complex : public std::complex<double>
{
public:
    complex(double real, double imag);
    complex square() const;
    double norm() const;
    double squaredNorm() const;
};

#endif // COMPLEX_H
