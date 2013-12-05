#include "imagegenerator.h"
#include "gradient.h"
#include "logger.h"
#include "matrix.h"
#include <QImage>

ImageGenerator::ImageGenerator() :
        gradient(new Gradient(":/palettes/default.palette"))
{
}

QImage *ImageGenerator::generateImage(Matrix *m) const
{
    QImage *result = new QImage(m->size(), QImage::Format_RGB32);
    for (int x=0; x<result->width(); x++)
        for (int y=0; y<result->height(); y++)
            result->setPixel(x, y, gradient->getColorF(m->get(x,y)).rgb());
    return result;
}

void ImageGenerator::setGradient(Gradient *gradient)
{
    this->gradient = gradient;
}

Gradient *ImageGenerator::getGradient()
{
    return this->gradient;
}
