#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

namespace Ui {
    class MainWindow;
}

class Viewport;
class ImageGenerator;
class Matrix;
class QAction;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    Viewport *vp;
    ImageGenerator *ig;
    QList<Matrix*> models;
    QString lastDir;
    typedef struct {double xCenter, yCenter, range;} Coords;
    QList<Coords> coords;
    QAction *backButton;

private slots:
    void generate();
    void colorize();
    void setBoundaries(QRect);
    void move(double x, double y);
    void loadPalette();
    void savePalette();
    void editPalette();
    void back();
    void zoomOut();
    void reset();
    void showHelp();
};

#endif // MAINWINDOW_H
