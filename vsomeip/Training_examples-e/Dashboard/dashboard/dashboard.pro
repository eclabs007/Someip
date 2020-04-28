TEMPLATE = app
TARGET = dashboard
INCLUDEPATH += .
QT += quick

SOURCES += \
    main.cpp \
    cluster.cpp \
    communication.cpp \

RESOURCES += \
    dashboard.qrc

OTHER_FILES += \
    qml/dashboard.qml \
    qml/DashboardGaugeStyle.qml \
    qml/IconGaugeStyle.qml \
    qml/TachometerStyle.qml \
    qml/TurnIndicator.qml \
    qml/ValueSource.qml

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols/extras/dashboard
INSTALLS += target

HEADERS += \
    cluster.h \
    communication.h
LIBS += -pthread
LIBS += -lvsomeip  -lboost_system -lboost_thread -lboost_log -lboost_filesystem
#INCLUDEPATH += /home/vagrant/QT/inc/interface
#DEPENDPATH += /home/vagrant/QT/libv

QMAKE_LFLAGS += -lvsomeip
QMAKE_CXXFLAGS += -std=c++0x
