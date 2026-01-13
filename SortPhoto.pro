QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    getting_exifdata.cpp \
    main.cpp \
    mainwindow.cpp \
    sorting_photo.cpp

HEADERS += \
    getting_exifdata.h \
    mainwindow.h \
    sorting_photo.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/lib/exiv2-mingw/include
LIBS += -L$$PWD/lib/exiv2-mingw/lib -lexiv2
LIBS_DIR = $$PWD/lib/exiv2-mingw/lib

defineTest(copyToDestDir) {
    files = $$1
    dir = $$2
    win32:dir ~= s,/,\\,g

    for(file, files) {
        win32:file ~= s,/,\\,g
        QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$shell_quote($$file) $$shell_quote($$dir) $$escape_expand(\\n\\t)
    }
    export(QMAKE_POST_LINK)
}

copyToDestDir($$LIBS_DIR, $$OUT_PWD/debug)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
