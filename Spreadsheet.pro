#-------------------------------------------------
#
# Project created by QtCreator 2015-11-19T10:47:46
#
#-------------------------------------------------

QT       += core gui

TARGET = Spreadsheet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spreadsheet.cpp \
    gotocell_dialog.cpp \
    cell.cpp

HEADERS  += mainwindow.h \
    spreadsheet.h \
    gotocell_dialog.h \
    cell.h

FORMS    += mainwindow.ui \
    gotocell_dialog.ui

RESOURCES += \
    Spreadsheet.qrc
