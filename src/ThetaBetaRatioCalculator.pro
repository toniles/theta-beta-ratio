QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ThetaBetaRatioCalculator
TEMPLATE = app

SOURCES += main.cpp \
           MainWindow.cpp \
           LogicHandler.cpp  

HEADERS  += MainWindow.h \
            LogicHandler.h  

INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt6/QtWidgets
