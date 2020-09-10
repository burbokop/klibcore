#include "klocalretranslator.h"

#include <QDateTime>
#include <QTcpSocket>
#include <QTimer>

void KLocalRetranslator::setConnections(QList<QTcpSocket *> list) {
    QList<QTcpSocket*> aa = list;
    QStringList result;
    for(QTcpSocket *a : aa) {
        result.push_back(QString::number(reinterpret_cast<uintptr_t>(a)));
    }
    setConnections(result);
}

KLocalRetranslator::KLocalRetranslator(QObject *parent) : QObject(parent) {
    connect(server, &QTcpServer::newConnection, this, &KLocalRetranslator::onNewConnection);
    server->listen();
    QTimer *broadcustTimer = new QTimer();
    connect(broadcustTimer, &QTimer::timeout, this, &KLocalRetranslator::writeProadcust);
    broadcustTimer->start(1000);
    setHostPort(server->serverPort());
    setHostAddress(KLocalConnector::generateMachineAddress());
    connect(this, &KLocalRetranslator::broadcastIntervalChanged, broadcustTimer, [broadcustTimer](auto value){
        broadcustTimer->setInterval(value);
    });
    setCreationTime(QDateTime::currentMSecsSinceEpoch());
}

void KLocalRetranslator::writeAll(const QByteArray &data, QTcpSocket *exclusion) {
    for(auto it = agregators.begin(); it != agregators.end(); ++it) {
        if(it.key() != exclusion && it.key() != nullptr) {
            it.value()->writeFrame(data);
        }
    }
}

void KLocalRetranslator::writeProadcust() {
    localConnector.writeDatagram(server, port(), creationTime());
}

void KLocalRetranslator::onNewConnection() {
    QTcpSocket *client = server->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, this, &KLocalRetranslator::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &KLocalRetranslator::onDisconnected);
    agregators[client] = new KFrameAgregator(client);

    setConnections(agregators.keys());
}

void KLocalRetranslator::onReadyRead() {
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(sender());
    auto agr = agregators[senderSocket];
    while (agr->hasFrameBuffered()) {
        auto&& frame = agr->readFrame();
        writeAll(frame, senderSocket);
    }
}

void KLocalRetranslator::onDisconnected() {
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(sender());
    agregators.remove(senderSocket);

    setConnections(agregators.keys());
}
