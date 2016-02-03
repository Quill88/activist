#include "camcontroller.h"
#include "srcEmail/SmtpMime.h"
#include <QQmlProperty>
#include <QList>
#include <QObject>
#include <QtSql>

camController::camController()
{

}

void camController::init()
{
    pos = "!error in taking GPS coordinate!";
    source = QGeoPositionInfoSource::createDefaultSource(this);
    if (source) {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
            this, SLOT(positionUpdated(QGeoPositionInfo)));
        source->startUpdates();
    }

    dbWorking();

    fview.setSource(QUrl("qrc:/first.qml"));
    fview.resize(800, 480);
    fview.rootContext()->setContextProperty("myObj", this);
    QQmlContext* context = fview.rootContext();
    context->setContextProperty("myObj", this);
    context->setContextProperty("myModel", QVariant::fromValue(dataList));

    fview.show();
}

void camController::dbWorking()
{
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

    db.setDatabaseName("smartCam.sqlite");

    if( !db.open() )
    {
      qDebug() << db.lastError();
    }
    else qDebug( "Connected!" );

    QSqlQuery a_query;
       // DDL query
       QString str = "CREATE TABLE contacts ("
               "number integer PRIMARY KEY NOT NULL, "
               "name VARCHAR(255), "
               "address VARCHAR(255)"
               ");";
       bool b = a_query.exec(str);
       if (!b) {
           qDebug() << "Вроде не удается создать таблицу";
       }

       // DML
       QString str_insert = "INSERT INTO contacts(number, name, address) "
               "VALUES (%1, '%2', '%3');";
       str = str_insert.arg("1").arg("Утечка воды").arg("messenger.vodokanal@gmail.com");
       b = a_query.exec(str);
       str = str_insert.arg("2").arg("ДТП").arg("messenger.vodokanal@gmail.com");
       b = a_query.exec(str);
       str = str_insert.arg("3").arg("Мусор на улицах").arg("messenger.vodokanal@gmail.com");
       b = a_query.exec(str);
       str = str_insert.arg("4").arg("Бродячие животные").arg("messenger.vodokanal@gmail.com");
       b = a_query.exec(str);
       if (!b) {
           qDebug() << "Кажется данные не вставляются";
       }
       if (!a_query.exec("SELECT name FROM contacts")) {
           qDebug() << "Даже селект не получается";\
       }
       QSqlRecord rec = a_query.record();
       //int number = 0;
       QString name = "";

       while (a_query.next()) {
           //number = a_query.value(rec.indexOf("number")).toInt();
           name = a_query.value(rec.indexOf("name")).toString();

           qDebug() //<< "key " << number
                    << "name " << name;

           dataList.append(name);
       }
}

void camController::sendPhoto(const QString &img)
{
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

    smtp.setUser("messenger.vodokanal@gmail.com");
    smtp.setPassword("asdfg0987654321hjkl");

    MimeMessage message;

    EmailAddress sender("messenger.vodokanal@gmail.com", "Messenger");
    message.setSender(&sender);

    EmailAddress to(mainAdress, "Message");
    message.addRecipient(&to);

    message.setSubject(mainSubject);

    MimeText txt;
    txt.setText(pos);
    message.addPart(&txt);

        // Now we create the attachment object
    MimeAttachment attachment(new QFile(img));
        // the file type can be setted. (by default is application/octet-stream)
    attachment.setContentType("image/jpg");

        // Now add it to message
    message.addPart(&attachment);

    mess = "";

    if (!smtp.connectToHost()) {
        mess+="Failed to connect to host!\n";
    }
    else if (!smtp.login()) {
        mess+="Failed to login!\n";
    }
    else if (!smtp.sendMail(message)) {
        mess+="Failed to send mail!\n";
    }

    if (mess=="") {
        mess+="Mail send!";
    }

    qDebug() << mess;

    smtp.quit();

    if(source)
        source->stopUpdates();
}

void camController::positionUpdated(const QGeoPositionInfo &info)
{
    qDebug() << "Position updated:" << info;
    QGeoCoordinate coordinate = info.coordinate();
    pos = coordinate.toString();
}

void camController::quitFirst(QString subject)
{
    mainSubject = subject;
    qDebug()<<subject;
    QSqlQuery a_query;
    QString str_q = "SELECT address FROM contacts "
                    "WHERE name = '%1';";
    if (!a_query.exec(str_q.arg(subject))) {
        qDebug() << "Селект не получился";\
    }

    QSqlRecord rec = a_query.record();
    QString address = "";

    while (a_query.next()) {
        address = a_query.value(rec.indexOf("address")).toString();
     mainAdress = address;
     qDebug() << address;
    }

    fview.close();

    view.setResizeMode(QQuickView::SizeRootObjectToView);

    QObject::connect(view.engine(), SIGNAL(quit()), qApp, SLOT(quit()));

    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.resize(800, 480);

    QTFile = view.rootObject();
    view.rootContext()->setContextProperty("myObject", this);
    view.show();
}

void camController::quit()
{
    fview.close();
}
