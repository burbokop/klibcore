#ifndef KLOCALSYNCRONIZER_H
#define KLOCALSYNCRONIZER_H

#include "kframeagregator.h"
#include "klocalconnector.h"

#include <QObject>
#include <QTcpSocket>
#include <src/kmacro.h>

class KLocalSyncronizer : public QObject {
    Q_OBJECT
    K_QML_TYPE(KLocalSyncronizer)
    QTcpSocket *newSocket();

    QTcpSocket *socket = new QTcpSocket(this);
    KFrameAgregator *frameAgregator = new KFrameAgregator(this);
    KLocalConnector *localCnnector = new KLocalConnector(this);

public:
    explicit KLocalSyncronizer(QObject *parent = nullptr);

public slots:
    bool write(const QByteArray &data);
    void bind(quint16 port);

signals:
    void frameReady(QByteArray data);
};


#endif // KLOCALSYNCRONIZER_H
