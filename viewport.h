#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QWidget>
#include <QRect>
#include <QColor>

class QImage;

class Viewport : public QWidget
{
    Q_OBJECT
public:
    Viewport(QWidget *parent=NULL);
    void setImage(QImage *image);
    void setClearColor(QColor color);
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    QImage *image;
    QRect zoomRegion;
    QPoint mouseLastPos;
    int deltaX, deltaY;
    QColor clearColor;
signals:
    void resized();
    void zoomed(QRect zoomRegion);
    void moved(double x, double y);

};

#endif // VIEWPORT_H
