#include "documenthandler.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/icon.ico"));

    // QQuickStyle::setStyle("Universal");
    QQuickStyle::setStyle("Fusion");
    qmlRegisterType<DocumentHandler>("org.qtproject.example", 1, 0, "DocumentHandler");
    QQmlApplicationEngine engine(QUrl("qrc:/qml/main.qml"));
    return a.exec();
}
