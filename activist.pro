TEMPLATE = app

QT += core network positioning quick qml multimedia sql

SOURCES += main.cpp \
    camcontroller.cpp \
    srcEmail/emailaddress.cpp \
    srcEmail/mimeattachment.cpp \
    srcEmail/mimecontentformatter.cpp \
    srcEmail/mimefile.cpp \
    srcEmail/mimehtml.cpp \
    srcEmail/mimeinlinefile.cpp \
    srcEmail/mimemessage.cpp \
    srcEmail/mimemultipart.cpp \
    srcEmail/mimepart.cpp \
    srcEmail/mimetext.cpp \
    srcEmail/quotedprintable.cpp \
    srcEmail/smtpclient.cpp

RESOURCES += \
    qml.qrc

QML_IMPORT_PATH =

include(deployment.pri)

HEADERS += \
    camcontroller.h \
    srcEmail/emailaddress.h \
    srcEmail/mimeattachment.h \
    srcEmail/mimecontentformatter.h \
    srcEmail/mimefile.h \
    srcEmail/mimehtml.h \
    srcEmail/mimeinlinefile.h \
    srcEmail/mimemessage.h \
    srcEmail/mimemultipart.h \
    srcEmail/mimepart.h \
    srcEmail/mimetext.h \
    srcEmail/quotedprintable.h \
    srcEmail/smtpclient.h \
    srcEmail/smtpexports.h \
    srcEmail/SmtpMime.h

CONFIG += mobility
MOBILITY = location

    addFiles.sources = /usr/local/bin/smartCam.sqlite
    addFiles.path = .
    DEPLOYMENT += addFiles