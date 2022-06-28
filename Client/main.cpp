#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <client.h>
#include <QQmlContext>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    Client c;
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("client", &c);
    qmlRegisterType<Client>("ClientModule", 1, 0, "Client");
    engine.load(url);

    return app.exec();
}
