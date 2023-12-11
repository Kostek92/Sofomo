#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "AppController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    AppController *playerController = new AppController(&app);
    qmlRegisterSingletonInstance("app.AppController", 1, 0, "AppController", playerController);
    const QUrl url(u"qrc:/Sofomo/src/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
