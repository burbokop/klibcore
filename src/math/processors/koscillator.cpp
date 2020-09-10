#include "koscillator.h"
#include <math.h>
#include <QtMath>

double KOscillator::frequency() const {
    return m_frequency;
}

void KOscillator::setFrequency(double frequency) {
    m_frequency = frequency;
}

double KOscillator::phase() const {
    return m_phase;
}

void KOscillator::setPhase(double phase) {
    m_phase = phase;
}

double KOscillator::amplitude() const {
    return m_amplitude;
}

void KOscillator::setAmplitude(double amplitude) {
    m_amplitude = amplitude;
}

KOscillator::KOscillator() {

}


double KOscillator::signal(double value, int channel) {
    //long double delta = t.nsecsElapsed() * 0.000001;
    //t.restart();

    m_frequency *= 1.000001;

    (void)value;
    auto maxFrequency = 48000;

    if(channel >= channelsData.size()) {
        channelsData.resize(channel + 1);
        channelsData[channel] = 0;
    }

    m_frequency = std::min(m_frequency, static_cast<double>(maxFrequency));
    double arg = 2 * M_PI * m_frequency * (channelsData[channel]++ % maxFrequency + 1) / maxFrequency + m_phase;
    return m_amplitude * qFastSin(arg);
}
