#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H

#include <QSize>

class Gradient;
class QImage;
class Matrix;

class ImageGenerator
{
public:
    ImageGenerator();
    QImage *generateImage(Matrix*) const;
    void setGradient(Gradient *gradient);
    Gradient *getGradient();
private:
    Gradient *gradient;
};

#endif // IMAGEGENERATOR_H
