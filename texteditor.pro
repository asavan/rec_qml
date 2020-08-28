QT += qml quick
TARGET = texteditor
# !no_desktop: QT += widgets

include(src/src.pri)
# include(../shared/shared.pri)

OTHER_FILES += \
    qml/main.qml \
    qml/MyBigButton.qml


RESOURCES += \
    resources.qrc

RC_ICONS = icon.ico
