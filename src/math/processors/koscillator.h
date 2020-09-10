#ifndef KOSCILLATOR_H
#define KOSCILLATOR_H

#include "ksignalprocessor.h"

#include <QElapsedTimer>
#include <QVector>


class KOscillator : public KSignalProcessor {
    K_OBJECT
    double m_frequency = 36000;
    double m_phase = 0;
    double m_amplitude = 1;

    QVector<quint64> channelsData;

    QElapsedTimer t;
public:
    KOscillator();

    // KSignalProcessor interface
    double frequency() const;
    void setFrequency(double frequency);

    double phase() const;
    void setPhase(double phase);

    double amplitude() const;
    void setAmplitude(double amplitude);

protected:
    double signal(double value, int channel) override;
};

#endif // KOSCILLATOR_H
