#ifndef CAMCONTROLLER_H
#define CAMCONTROLLER_H

#include <QtCore>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQuickItem>
#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>
#include <QGeoCoordinate>
#include <QtSql>
#include <QQuickView>
#include <QQmlEngine>

class camController : public QObject
{
    Q_OBJECT
public:
    camController();
    void init();
    QString mess;
signals:

public slots:
    void sendPhoto(const QString &img);
    void quitFirst(QString subject);
    void quit();
protected:
    QQuickItem *QTFile;
    QQuickView view;
    QQuickView fview;
private slots:
    void positionUpdated(const QGeoPositionInfo &info);

private:
    QString pos;
    QGeoPositionInfoSource *source;
    void dbWorking();
    QStringList dataList;
    QString mainAdress;
    QString mainSubject;
};

#endif // CAMCONTROLLER_H
