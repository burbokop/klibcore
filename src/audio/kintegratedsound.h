#ifndef KINTEGRATEDSOUND_H
#define KINTEGRATEDSOUND_H

#include "ksound.h"

#include <QElapsedTimer>
#include <QVector>



class KIntegratedSound : public KSound {
    Q_OBJECT
    KSound *m_child;
    QVector<double> m_amplitudes;
    QElapsedTimer elapsedFromStart;
    qint64 m_interval = 0;
    int m_discretizeCount = 0;
public:
    KIntegratedSound(bool play = false, QObject *parent = nullptr);
    void reset();

    // KSound interface
    KSound *child() const;
    void setChild(KSound *child);

    QVector<double> amplitudes() const;
    void setAmplitudes(const QVector<double> &amplitudes);
    void setAmplitudes(const QVariantList &amplitudes);

    qint64 interval() const;
    void setInterval(const qint64 &interval);

    int discretizeCount() const;
    void setDiscretizeCount(int discretizeCount);

protected:
    double signal(qint64 index) override;
};

#endif // KINTEGRATEDSOUND_H
