/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickItem>
#include <QSharedPointer>

#include <QThread>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QDebug>
#include <QQmlProperty>
#include <QString>
#include "pthread.h"
#include "communication.h"
#include <cluster.h>
Cluster *cluster;

pthread_t tid_com;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
    app.setFont(QFont("DejaVu Sans"));
    cluster=Cluster::instance();


    QQmlApplicationEngine engine(QUrl("qrc:/qml/dashboard.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    engine.rootContext()->setContextProperty("Cluster",cluster);

    cluster->setSpeed(QVariant(280));
    cluster->setRpm(8);
    cluster->setTemp(10);
    cluster->setFuel(10);
    pthread_create(&tid_com,NULL,init_communication,NULL);

    return app.exec();
}
