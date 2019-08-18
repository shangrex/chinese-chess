#-------------------------------------------------
#
# Project created by QtCreator 2019-04-22T17:30:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pd2-boardgame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
QT += network
SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/16pic_4872756_b.jpg \
    src/16pic_4872756_b.jpg \
    src/Xiangqi_ad1.svg.png \
    src/Xiangqi_al1.svg.png \
    src/Xiangqi_cd1.svg.png \
    src/Xiangqi_cl1.svg.png \
    src/Xiangqi_ed1.svg.png \
    src/Xiangqi_el1.svg.png \
    src/Xiangqi_gd1.svg.png \
    src/Xiangqi_gl1.svg.png \
    src/Xiangqi_hd1.svg.png \
    src/Xiangqi_hl1.svg.png \
    src/Xiangqi_rd1.svg.png \
    src/Xiangqi_rl1.svg.png \
    src/Xiangqi_sd1.svg.png \
    src/Xiangqi_sl1.svg.png \
    src/16pic_4872756_b_opt.jpg \
    src/old.jpg \
    src/Xiangqi_ad1.svg.png \
    src/Xiangqi_al1.svg.png \
    src/Xiangqi_cd1.svg.png \
    src/Xiangqi_cl1.svg.png \
    src/Xiangqi_ed1.svg.png \
    src/Xiangqi_el1.svg.png \
    src/Xiangqi_gd1.svg.png \
    src/Xiangqi_gl1.svg.png \
    src/Xiangqi_hd1.svg.png \
    src/Xiangqi_hl1.svg.png \
    src/Xiangqi_rd1.svg.png \
    src/Xiangqi_rl1.svg.png \
    src/Xiangqi_sd1.svg.png \
    src/Xiangqi_sl1.svg.png \
    src/16pic_4872756_b_opt.jpg \
    src/old.jpg \
    src/Xiangqi_ad1.svg.png \
    src/Xiangqi_al1.svg.png \
    src/Xiangqi_cd1.svg.png \
    src/Xiangqi_cl1.svg.png \
    src/Xiangqi_ed1.svg.png \
    src/Xiangqi_el1.svg.png \
    src/Xiangqi_gd1.svg.png \
    src/Xiangqi_gl1.svg.png \
    src/Xiangqi_hd1.svg.png \
    src/Xiangqi_hl1.svg.png \
    src/Xiangqi_rd1.svg.png \
    src/Xiangqi_rl1.svg.png \
    src/Xiangqi_sd1.svg.png \
    src/Xiangqi_sl1.svg.png \
    src/16pic_4872756_b_opt.jpg \
    src/old.jpg \
    src/Xiangqi_ad1.svg.png \
    src/Xiangqi_al1.svg.png \
    src/Xiangqi_cd1.svg.png \
    src/Xiangqi_cl1.svg.png \
    src/Xiangqi_ed1.svg.png \
    src/Xiangqi_el1.svg.png \
    src/Xiangqi_gd1.svg.png \
    src/Xiangqi_gl1.svg.png \
    src/Xiangqi_hd1.svg.png \
    src/Xiangqi_hl1.svg.png \
    src/Xiangqi_rd1.svg.png \
    src/Xiangqi_rl1.svg.png \
    src/Xiangqi_sd1.svg.png \
    src/Xiangqi_sl1.svg.png \
    src/16pic_4872756_b_opt.jpg \
    src/old.jpg \
    src/oldguard.png \
    src/Xiangqi_ad1_opt.png \
    src/Xiangqi_al1.svg.png \
    src/Xiangqi_cd1.svg.png \
    src/Xiangqi_cl1.svg.png \
    src/Xiangqi_ed1.svg.png \
    src/Xiangqi_el1.svg.png \
    src/Xiangqi_gd1.svg.png \
    src/Xiangqi_gl1.svg.png \
    src/Xiangqi_hd1.svg.png \
    src/Xiangqi_hl1.svg.png \
    src/Xiangqi_rd1.svg.png \
    src/Xiangqi_rl1.svg.png \
    src/Xiangqi_sd1.svg.png \
    src/Xiangqi_sl1.svg.png \
    src/old.jpg \
    src/old_resized.jpg \
    src/oldguard.png \
    src/Xiangqi_ad1_opt.png \
    src/Xiangqi_al1.svg.png \
    src/Xiangqi_cd1.svg.png \
    src/Xiangqi_cl1.svg.png \
    src/Xiangqi_ed1.svg.png \
    src/Xiangqi_el1.svg.png \
    src/Xiangqi_gd1.svg.png \
    src/Xiangqi_gl1.svg.png \
    src/Xiangqi_hd1.svg.png \
    src/Xiangqi_hl1.svg.png \
    src/Xiangqi_rd1.svg.png \
    src/Xiangqi_rl1.svg.png \
    src/Xiangqi_sd1.svg.png \
    src/Xiangqi_sl1.svg.png

RESOURCES += \
    resource.qrc
