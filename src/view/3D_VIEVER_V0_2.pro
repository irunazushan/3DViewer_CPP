QT       += core gui opengl widgets openglwidgets

include(qgifimage/gifimage/qtgifimage.pri)

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cc \
    ../model/model.cc \
    ../model/parser.cc \
    ../model/transformer_strategy.cc \
    glview.cc \
    main.cc \
    viever.cc

HEADERS += \
    ../controller/controller.h \
    ../model/model.h \
    glview.h \
    viever.h

FORMS += \
    viever.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
