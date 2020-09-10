#ifndef KAMPLITUDETRANSFORMER_H
#define KAMPLITUDETRANSFORMER_H

#include "ksound.h"

#include <QElapsedTimer>
#include <functional>

class KAmplitudeTransformer : public KSound {
    KSound *m_child = nullptr;
    std::function<double(qint64)> m_functinon;
    QElapsedTimer elapsedFromStart;
    qint64 m_interval;
public:
    KAmplitudeTransformer(bool play, QObject *parent);
    KSound *child() const;
    void setChild(KSound *child);
    std::function<double (qint64)> functinon() const;
    void setFunctinon(const std::function<double (qint64)> &functinon);
    qint64 interval() const;
    void setInterval(const qint64 &interval);
    void reset();

    // KSound interface
protected:
    double signal(qint64 index) override;
};

#endif // KAMPLITUDETRANSFORMER_H
