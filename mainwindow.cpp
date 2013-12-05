#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagegenerator.h"
#include "mandelbrotgenerator.h"
#include "viewport.h"
#include "gradient.h"
#include "gradienteditor.h"
#include "progressdialog.h"
#include "matrix.h"
#include <QFileDialog>
#include <QAction>
#include <QMessageBox>
#include <cassert>

#define XCENTER -0.5
#define YCENTER 0.0
#define RANGE 2.0

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    vp(new Viewport(this)),
    ig(new ImageGenerator()),
    models(),
    lastDir("."),
    coords()
{
    ui->setupUi(this);
    setCentralWidget(vp);
    connect(this->vp, SIGNAL(zoomed(QRect)), this, SLOT(setBoundaries(QRect)));
    connect(this->vp, SIGNAL(moved(double,double)), this, SLOT(move(double,double)));
    QAction *open, *save, *edit, *zoomOut, *reset, *help;
    ui->toolBar->addAction(open = new QAction(QIcon(":/icons/open.png"),"Load palette", this));
    ui->toolBar->addAction(save = new QAction(QIcon(":/icons/save.png"), "Save palette", this));
    ui->toolBar->addAction(edit = new QAction(QIcon(":/icons/edit.png"), "Edit palette", this));
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(backButton = new QAction(QIcon(":/icons/back.png"), "Back", this));
    ui->toolBar->addAction(zoomOut = new QAction(QIcon(":/icons/zoomout.png"), "Zoom out", this));
    ui->toolBar->addAction(reset = new QAction(QIcon(":/icons/reset.png"), "Reset zoom", this));
    ui->toolBar->addAction(help = new QAction(QIcon(":/icons/help.png"),"Help",this));
    connect(open, SIGNAL(triggered()), this, SLOT(loadPalette()));
    connect(save, SIGNAL(triggered()), this, SLOT(savePalette()));
    connect(edit, SIGNAL(triggered()), this, SLOT(editPalette()));
    connect(backButton, SIGNAL(triggered()), this, SLOT(back()));
    connect(zoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(reset, SIGNAL(triggered()), this, SLOT(reset()));
    connect(help, SIGNAL(triggered()), this, SLOT(showHelp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    Coords newCoords;
    newCoords.range = RANGE;
    newCoords.xCenter = XCENTER;
    newCoords.yCenter = YCENTER;
    coords.push_back(newCoords);
    generate();
    backButton->setEnabled(false);
//    connect(vp, SIGNAL(resized()), this, SLOT(generate()));
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::generate()
{
    MandelbrotGenerator *mg = new MandelbrotGenerator(vp->size(), coords.last().xCenter, coords.last().yCenter, coords.last().range);
    ProgressDialog *pd = new ProgressDialog("Processing...", "Calculating Mandelbrot set, please wait...", this);
    connect(mg, SIGNAL(finished()), pd, SLOT(accept()));
    mg->start();
    pd->exec();
    models.push_back(mg->getResult());
    colorize();
    delete mg;
    delete pd;
    backButton->setEnabled(true);
}

void MainWindow::colorize()
{
    assert(models.size()==coords.size());
    vp->setClearColor(ig->getGradient()->getColor(0));
    if (!models.empty())
        vp->setImage(ig->generateImage(models.back()));
}

void MainWindow::setBoundaries(QRect boundaries)
{
    Coords newCoords(coords.last());
    newCoords.xCenter = newCoords.xCenter + (double(boundaries.center().x())/vp->width() - 0.5)*newCoords.range;
    newCoords.yCenter = newCoords.yCenter - (double(boundaries.center().y())/vp->height() - 0.5)*newCoords.range;
    if (boundaries.width() > boundaries.height())
    {
        newCoords.range = newCoords.range * double(boundaries.width())/vp->width();
    }
    else
    {
        newCoords.range = newCoords.range * double(boundaries.height())/vp->height();
    }
    coords.push_back(newCoords);
    generate();
}

void MainWindow::move(double x, double y)
{
    Coords newCoords(coords.last());
    newCoords.xCenter -= x*newCoords.range;
    newCoords.yCenter += y*newCoords.range;
    coords.push_back(newCoords);
    generate();
}

void MainWindow::loadPalette()
{
    QString filepath = QFileDialog::getOpenFileName(this, QString("Select the palette to load"), lastDir, "Palettes (*.palette)");
    if (filepath == NULL) return;
    lastDir = filepath.left(filepath.lastIndexOf(QChar('/')));
    delete ig->getGradient();
    ig->setGradient(new Gradient(filepath));
    colorize();
}

void MainWindow::savePalette()
{
    QString filepath = QFileDialog::getSaveFileName(this, QString("Save current palette as..."), lastDir+QString("/myPaletteFile"), "Palettes (*.palette)");
    if (filepath == NULL) return;
    lastDir = filepath.left(filepath.lastIndexOf(QChar('/')));
    if (!filepath.endsWith(".palette", Qt::CaseInsensitive))
        filepath = filepath.append(".palette");
    ig->getGradient()->save(filepath);
}

void MainWindow::editPalette()
{
    GradientEditor *ge = new GradientEditor(new Gradient(*ig->getGradient()), this);
    ge->exec();
    if (ge->result() == QDialog::Accepted)
    {
        delete ig->getGradient();
        ig->setGradient(ge->getGradient());
        colorize();
    }
}

void MainWindow::back()
{
    Matrix* garbage = models.last();
    models.pop_back();
    delete garbage;
    coords.pop_back();
    colorize();
    if (models.size() == 1)
        backButton->setEnabled(false);
}

void MainWindow::zoomOut()
{
    Coords newCoords(coords.last());
    newCoords.range *= 2;
    coords.push_back(newCoords);
    generate();
}

void MainWindow::reset()
{
    coords.push_back(coords.first());
    models.push_back(new Matrix(models.first()));
    backButton->setEnabled(true);
    colorize();
}

void MainWindow::showHelp()
{
    QMessageBox box(this);
    box.setWindowTitle("Help");
    box.setText("Zoom In: Drag the pointer pressing LEFT mouse button, to create a rectangle. Then left-click the selected area to generate that specific zone. Clicking outside the rectangle lets you make a new rectangle.\n\nZoom Out: The button \"Zoom out\" in the toolbar reduces the zoom in the current area by a half.\n\nNavigation: Drag the picture while pressing the RIGHT mouse button to select a nearby area. The fractal is generated when you release the button.");
    box.exec();
}
