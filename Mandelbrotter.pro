# -------------------------------------------------
# Project created by QtCreator 2010-04-28T20:05:21
# -------------------------------------------------
TARGET = Mandelbrotter
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    viewport.cpp \
    mandelbrotcalculator.cpp \
    basicmandelbrotcalculator.cpp \
    complex.cpp \
    logger.cpp \
    stopeditor.cpp \
    stop.cpp \
    gradientviewer.cpp \
    gradienteditor.cpp \
    gradient.cpp \
    mandelbrotgenerator.cpp \
    imagegenerator.cpp \
    matrix.cpp \
    progressdialog.cpp
HEADERS += mainwindow.h \
    viewport.h \
    mandelbrotcalculator.h \
    basicmandelbrotcalculator.h \
    complex.h \
    logger.h \
    stopeditor.h \
    stop.h \
    gradientviewer.h \
    gradienteditor.h \
    gradient.h \
    mandelbrotgenerator.h \
    imagegenerator.h \
    matrix.h \
    progressdialog.h
FORMS += mainwindow.ui \
    stopeditor.ui \
    gradienteditor.ui \
    progressdialog.ui
RESOURCES += resources.qrc
QMAKE_CXXFLAGS_DEBUG += -g0 -O3
