#ifndef KLOCALRETRANSLATOR_H
#define KLOCALRETRANSLATOR_H

#include "kframeagregator.h"
#include "klocalconnector.h"

#include <QObject>
#include <QTcpServer>
#include <QUdpSocket>
#include <src/kmacro.h>

class KLocalRetranslator : public QObject {
    Q_OBJECT
    QTcpServer *server = new QTcpServer(this);
    QMap<QTcpSocket*, KFrameAgregator*> agregators;
    QUdpSocket *broadcust = new QUdpSocket(this);

    K_READONLY_PROPERTY(QStringList, connections, connections, setConnections, connectionsChanged, QStringList());
    K_READONLY_PROPERTY(qint64, creationTime, creationTime, setCreationTime, creationTimeChanged, 0);
    K_AUTO_PROPERTY(quint16, port, port, setPort, portChanged, 2361)
    K_AUTO_PROPERTY(int, broadcastInterval, broadcastInterval, setBroadcastInterval, broadcastIntervalChanged, 1000)
    K_READONLY_PROPERTY(QString, hostAddress, hostAddress, setHostAddress, hostAddressChanged, QString())
    K_READONLY_PROPERTY(quint16, hostPort, hostPort, setHostPort, hostPortChanged, 0)
    void setConnections(QList<QTcpSocket*> list);

    KLocalConnector localConnector;
public:
    KLocalRetranslator(QObject *parent = nullptr);
public slots:
    void writeAll(const QByteArray &data, QTcpSocket *exclusion = nullptr);
    void writeProadcust();
private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
};

#endif // KLOCALRETRANSLATOR_H
