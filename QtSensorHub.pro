QT += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Altri elementi del tuo file .pro rimangono invariati

SOURCES += \
    grafo.cpp \
    main.cpp \
    newsensorpopup.cpp \
    pazienteitemwidget.cpp \
    schedapaziente.cpp \
    sensors/sensor.cpp \
    sensors/pressioneSensor.cpp \
    sensors/insulinaSensor.cpp \
    sensors/glucosioSensor.cpp \
    sensors/sensorHub.cpp \
    mainwindow.cpp

HEADERS += \
    grafo.h \
    newsensorpopup.h \
    pazienteitemwidget.h \
    schedapaziente.h \
    sensors/sensor.h \
    sensors/pressioneSensor.h \
    sensors/insulinaSensor.h \
    sensors/glucosioSensor.h \
    sensors/sensorHub.h \
    mainwindow.h

# Resto del tuo file .pro rimane invariato

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

