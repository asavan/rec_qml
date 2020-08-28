QT += quickcontrols2

TARGET = req_qml

include(src/src.pri)

OTHER_FILES += \
    qml/main.qml \
    qml/MyBigButton.qml


RESOURCES += \
    resources.qrc

RC_ICONS = images/icon.ico
