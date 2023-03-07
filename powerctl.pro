TEMPLATE = app
TARGET = powerctl
CONFIG = c99 link_pkgconfig
DEFINES = _GNU_SOURCE
INCLUDEPATH =
PKGCONFIG =

PKGCONFIG += tinyc

#PKGCONFIG += dbus-1
#PKGCONFIG += libusb
#PKGCONFIG += libxml-2.0
#PKGCONFIG += polkit-gobject-1
#PKGCONFIG += glib-2.0
#PKGCONFIG += gio-2.0

HEADERS = \
    asound.h \
    cpuload.h \
    sysidle.h \

SOURCES = \
    0Temp.c \
    asound.c \
    cpuload.c \
    main.c \
    sysidle.c \

DISTFILES = \
    install.sh \
    License.txt \
    meson.build \
    Readme.txt \


