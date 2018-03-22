QT += serialbus widgets

TARGET = can
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    connectdialog.cpp \
    bms.cpp \
    bmswindow.cpp

HEADERS += mainwindow.h \
    connectdialog.h \
    bms.h \
    bmswindow.h

FORMS   += mainwindow.ui \
    connectdialog.ui \
    bms.ui \
    bmswindow.ui

RESOURCES += can.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/serialbus/can
INSTALLS += target
