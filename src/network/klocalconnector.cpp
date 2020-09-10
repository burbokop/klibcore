#include "klocalconnector.h"

#include <QJsonDocument>
#include <QNetworkInterface>

KLocalConnector::KLocalConnector(QObject *parent) : QObject (parent) {}

void KLocalConnector::bind(quint16 port) {
    m_broadcustPort = port;
    socket->bind(port, QUdpSocket::ShareAddress);
}

void KLocalConnector::recieveDatagram() {
    if(socket->state() == QAbstractSocket::BoundState && socket->hasPendingDatagrams()) {
        QByteArray data;
        auto size = socket->pendingDatagramSize();
        data.resize(size);
        socket->readDatagram(data.data(), size);
        QVariantList list = QJsonDocument::fromJson(data).toVariant().toList();
        if(list.size() > 1) {
            m_hostAddress = list[0].toString();
            m_hostPort = list[1].toInt();
            hasData = true;
        }
    }
}

quint16 KLocalConnector::broadcustPort() const {
    return m_broadcustPort;
}

QString KLocalConnector::hostAddress() {
    if(hasData == false)
        recieveDatagram();

    return m_hostAddress;
}

quint16 KLocalConnector::hostPort() {
    if(hasData == false)
        recieveDatagram();

    return m_hostPort;
}

QList<KLocalConnector::DataItem> KLocalConnector::readAll() {
    QList<DataItem> result;
    while(socket->state() == QAbstractSocket::BoundState && socket->hasPendingDatagrams()) {
        QByteArray data;
        auto size = socket->pendingDatagramSize();
        data.resize(size);
        socket->readDatagram(data.data(), size);
        QVariantList list = QJsonDocument::fromJson(data).toVariant().toList();
        if(list.size() > 2) {
            result.push_back({ list[0].toString(), static_cast<quint16>(list[1].toInt()), static_cast<qint64>(list[2].value<qint64>()) });
        }
    }
    return result;
}

void KLocalConnector::reset() {
    m_hostAddress.clear();
    m_hostPort = 0;
    hasData = false;
}

void KLocalConnector::writeDatagram(QTcpServer *server, quint16 broadcustPort, qint64 time = 0) {
    socket->writeDatagram(QJsonDocument::fromVariant(QVariantList({ generateMachineAddress(), server->serverPort(), QVariant::fromValue<qint64>(time) })).toJson(), QHostAddress::Broadcast, broadcustPort);
}

QString KLocalConnector::generateMachineAddress() {
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty()) {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }
    return ipAddress;
}
