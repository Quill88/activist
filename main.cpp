#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include "camcontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    camController MyContr;
    MyContr.init();

    return app.exec();
}
