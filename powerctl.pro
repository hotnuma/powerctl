TEMPLATE = app
TARGET = powertool
CONFIG = c++11
DEFINES =
INCLUDEPATH =

HEADERS = \
    cpuload.h \
    sysidle.h \

SOURCES = \
    0Temp.cpp \
    cpuload.cpp \
    main.cpp \
    sysidle.cpp \

DISTFILES += \
    meson.build \
    install.sh \


