QT += core gui

TARGET = vProsojnice
TEMPLATE = app

win32:LIBS += libpoppler-qt4.dll

RESOURCES += resource.qrc

RC_FILE = icon.rc

HEADERS += mydoc.h \
           mainwidget.h

SOURCES += mydoc.cpp \
           mainwidget.cpp \
           main.cpp

FORMS += mainwidget.ui