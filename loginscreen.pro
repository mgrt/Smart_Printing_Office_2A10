QT       += core gui
QT       += core gui sql
QT       += network
QT       += core gui charts
QT       += printsupport
QT       += core gui multimedia multimediawidgets
QT       +=svg
QT       += core gui  serialport
QT       += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    categorie.cpp \
    chatconnection.cpp \
    commande.cpp \
    connection.cpp \
    employe.cpp \
    factures.cpp \
    machine.cpp \
    main.cpp \
    maintenance.cpp \
    mainwindow.cpp \
    modenuitjour.cpp \
    qcustomplot.cpp \
    qrcode.cpp \
    smtp.cpp \
    stocks.cpp

HEADERS += \
    arduino.h \
    categorie.h \
    chatconnection.h \
    commande.h \
    connection.h \
    employe.h \
    factures.h \
    machine.h \
    maintenance.h \
    mainwindow.h \
    modenuitjour.h \
    qcustomplot.h \
    qrcode.h \
    smtp.h \
    stocks.h

FORMS += \
    chatconnection.ui \
    mainwindow.ui

QMAKE_CXXFLAGS += -std=gnu++11
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Croix_Mundolsheim.png \
    changelog.txt \
    img/11639594308azjskddoutgi296zaayuhyuspofhahhfa4ezuhne7vcflkjlnicxnewkf17enf0janiemum3o1eikv5x9r1s6wst2obumnv3rmxj.png \
    img/decouvrir-businessman.png \
    img/icon-users-yellow.png \
    img/kindpng_202406.png \
    img/kindpng_2778486.png \
    img/logo sprint.png \
    img/logo sprint.png \
    img/print logo.png \
    img/print logo.png \
    img/wallpaperflare.com_wallpaper.jpg \
    map.qml \
    marker.png \
    marker.qml \
    rech.png

RESOURCES += \
    img.qrc \
    qml.qrc
QT += quick
