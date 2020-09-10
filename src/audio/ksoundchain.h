#ifndef KSOUNDCHAIN_H
#define KSOUNDCHAIN_H

#include "ksoundarray.h"

#include <QElapsedTimer>

class KSoundChain : public KSoundArray {
    Q_OBJECT
    QElapsedTimer stepTimer;
    qint64 m_interval = 1000;
    KSound *currentSound = nullptr;
    void switchSound();
public:
    KSoundChain(bool play = false, QObject *parent = nullptr);
    void reset();
    qint64 interval() const;
    void setInterval(const qint64 &interval);

    // KSound interface
protected:
    double signal(qint64 index) override;
};

#endif // KSOUNDCHAIN_H
