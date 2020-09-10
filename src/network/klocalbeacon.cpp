#include "klocalbeacon.h"

#include <QTimer>

#include <src/math/processors/knoisegenerator.h>


KLocalBeacon::KLocalBeacon(QObject *parent) : QObject(parent) {
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [timer, this](){
        timer->setInterval(KNoiseGenerator::percentRandom() * 2000);
        checkNetworkState();
    });
    connect(this, &KLocalBeacon::runningChanged, this, [timer](bool value){
        if(value) {
            timer->start(1000);
        } else {
            timer->stop();
        }
    });
}

bool KLocalBeacon::start(quint16 port) {
    if(!running()) {
        setRunning(true);
        setRunningPort(port);
        return true;
    }
    return false;
}

void KLocalBeacon::stop() {
    if(running()) {
        setRunning(false);
        setRunningPort(0);
        if(retranslator()) {
            delete retranslator();
            setRetranslator(nullptr);
        }
    }
}

void KLocalBeacon::checkNetworkState() {
    if(!localConnector) {
        localConnector = new KLocalConnector(this);
        localConnector->bind(runningPort());
    }
    auto socketList = localConnector->readAll();

    bool modeChanged = false;
    if(retranslator()) {
        for(auto pair : socketList) {
            if(pair.time < retranslator()->creationTime()) {
                modeChanged = true;
                break;
            }
        }

        if(modeChanged) {
            delete retranslator();
            setRetranslator(nullptr);
        }
    } else {
        bool isAllEmpty = true;
        for(auto pair : socketList) {
            if(!(pair.address.isEmpty() || pair.address == "null address")) {
                isAllEmpty = false;
            }
        }
        if(isAllEmpty) {
            retranslatorEnableCounter++;
        } else {
            retranslatorEnableCounter = 0;
        }

        if(retranslatorEnableCounter > 10) {
            setRetranslator(new KLocalRetranslator(this));
            retranslator()->setPort(runningPort());
            modeChanged = true;
            retranslatorEnableCounter = 0;
        }
    }

    if(modeChanged) {
        delete localConnector;
        localConnector = nullptr;
    }
}
