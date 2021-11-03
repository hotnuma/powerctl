TEMPLATE = app

TARGET = powerctl
CONFIG = c++11
DEFINES =
INCLUDEPATH =

HEADERS = \
    asound.h \
    cpuload.h \
    sysidle.h \

SOURCES = \
    0Temp.cpp \
    asound.cpp \
    cpuload.cpp \
    main.cpp \
    sysidle.cpp \

DISTFILES += \
    install.sh \
    License.txt \
    meson.build \
    Readme.txt \


