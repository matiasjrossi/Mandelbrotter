#include "viewport.h"
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QRect>

Viewport::Viewport(QWidget *parent) :
        QWidget(parent),
        image(NULL),
        zoomRegion(0,0,0,0),
        mouseLastPos(0,0),
        deltaX(0),
        deltaY(0),
        clearColor(Qt::black)
{
    setMouseTracking(true);
}

void Viewport::setImage(QImage *image)
{
    if (this->image != NULL) {
        delete this->image;
    }
    this->image = image;
    update();
}

void Viewport::setClearColor(QColor color)
{
    this->clearColor = color;
}

void Viewport::paintEvent(QPaintEvent *)
{
    if (image != NULL) {
        QPainter painter(this);
        painter.fillRect(QRect(0,0,this->width(), this->height()), clearColor);
        painter.drawImage(QPoint(deltaX,deltaY),*image);
        if (deltaX == 0 && deltaY == 0)
        {
            painter.setPen(Qt::yellow);
            painter.drawRect(zoomRegion);
        }
    }
}

void Viewport::resizeEvent(QResizeEvent *)
{
    emit resized();
}

void Viewport::mousePressEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        if (zoomRegion.contains(e->pos()))
        {
            emit zoomed(zoomRegion);
            zoomRegion = QRect(0,0,0,0);
        }
        else
        {
            zoomRegion.setTopLeft(e->pos());
            zoomRegion.setBottomRight(e->pos());
            update();
        }
    }
    else if (e->buttons() & Qt::RightButton)
    {
        mouseLastPos = e->pos();
    }
}

void Viewport::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        zoomRegion.setBottomRight(e->pos());
        update();
    }
    else if (e->buttons() & Qt::RightButton)
    {
        deltaX = e->pos().x() - mouseLastPos.x();
        deltaY = e->pos().y() - mouseLastPos.y();
        update();
    }
    else
    {
        if (zoomRegion.contains(e->pos()))
            setCursor(Qt::PointingHandCursor);
        else
            setCursor(Qt::ArrowCursor);
    }
}

void Viewport::mouseReleaseEvent(QMouseEvent *e)
{
    if (deltaX != 0 && deltaY != 0)
    {
        emit moved(double(deltaX)/width(), double(deltaY)/height());
        deltaX = deltaY = 0;
    }
}
