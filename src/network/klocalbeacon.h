#ifndef KLOCALBEACON_H
#define KLOCALBEACON_H

#include <src/network/klocalretranslator.h>

class KLocalBeacon : public QObject {
    Q_OBJECT
    K_QML_TYPE(KLocalBeacon)
    K_READONLY_PROPERTY(KLocalRetranslator*, retranslator, retranslator, setRetranslator, retranslatorChanged, nullptr);
    K_READONLY_PROPERTY(bool, running, running, setRunning, runningChanged, false);
    K_READONLY_PROPERTY(quint16, runningPort, runningPort, setRunningPort, runningPortChanged, 0);
    KLocalConnector *localConnector = nullptr;
    void checkNetworkState();
    int retranslatorEnableCounter = 0;
public:
    explicit KLocalBeacon(QObject *parent = nullptr);
public slots:
    bool start(quint16 port);
    void stop();

signals:

};

#endif // KLOCALBEACON_H
