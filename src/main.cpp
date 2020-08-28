#include "documenthandler.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication a(argc, argv);
    QQuickStyle::setStyle("Fusion");
    // QQuickStyle::setStyle("Universal");
    qmlRegisterType<DocumentHandler>("org.qtproject.example", 1, 0, "DocumentHandler");
    QQmlApplicationEngine engine(QUrl("qrc:/qml/main.qml"));
    return a.exec();
}
