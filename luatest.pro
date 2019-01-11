TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../lib64/release/ -llua
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../lib64/debug/ -llua
else:unix: LIBS += -L$$PWD/../../../lib64/ -llua

INCLUDEPATH += $$PWD/../../../lib64
DEPENDPATH += $$PWD/../../../lib64
