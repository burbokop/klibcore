#include "klocalsyncronizer.h"

#include <QTimer>

KLocalSyncronizer::KLocalSyncronizer(QObject *parent) : QObject(parent) {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        if(socket->state() == QAbstractSocket::UnconnectedState) {
            delete socket;
            socket = newSocket();
            socket->connectToHost(localCnnector->hostAddress(), localCnnector->hostPort());
        }
    });

    timer->start(1000);
}

bool KLocalSyncronizer::write(const QByteArray &data) {
    if(socket->state() == QAbstractSocket::ConnectedState) {
        frameAgregator->writeFrame(data);
        return true;
    }
    return false;
}

void KLocalSyncronizer::bind(quint16 port) {
    localCnnector->bind(port);
}

QTcpSocket *KLocalSyncronizer::newSocket() {
    QTcpSocket *result = new QTcpSocket();
    frameAgregator->setSocket(result);
    connect(result, &QTcpSocket::readyRead, this, [this]() {
        while(frameAgregator->hasFrameBuffered()) {
            emit frameReady(frameAgregator->readFrame());
        }
    });

    connect(result, &QTcpSocket::disconnected, this, [this]() {
        auto port = localCnnector->broadcustPort();
        delete  localCnnector;
        localCnnector = new KLocalConnector(this);
        localCnnector->bind(port);
    });
    return result;
}
