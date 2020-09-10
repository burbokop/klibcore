#ifndef KLOCALCONNECTOR_H
#define KLOCALCONNECTOR_H

#include <QObject>
#include <QTcpServer>
#include <QUdpSocket>

class KLocalConnector : public QObject {
    Q_OBJECT
    QUdpSocket *socket = new QUdpSocket(this);

    QString m_hostAddress = "null address";
    quint16 m_hostPort = 0;
    bool hasData = false;

    void recieveDatagram();

    quint16 m_broadcustPort = 0;
public:
    struct DataItem { QString address; quint16 port; qint64 time; };
    KLocalConnector(QObject *parent = nullptr);
    void bind(quint16 port);
    QString hostAddress();
    quint16 hostPort();
    QList<DataItem> readAll();
    void reset();

    void writeDatagram(QTcpServer *server, quint16 broadcustPort, qint64 time);
    static QString generateMachineAddress();
    quint16 broadcustPort() const;
};

inline QDebug &operator<<(QDebug &debug, const KLocalConnector::DataItem &item) {
    debug << item.address.toStdString().c_str() << ":" << item.port << ":" << item.time;
    return debug;
}

#endif // KLOCALCONNECTOR_H
