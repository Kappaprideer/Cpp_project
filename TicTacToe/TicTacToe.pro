TEMPLATE = app
TARGET = main

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    main.cpp
