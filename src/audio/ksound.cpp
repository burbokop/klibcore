#include "ksound.h"

qint64 KSound::sampleRate() const {
    return m_sampleRate;
}

void KSound::setSampleRate(const qint64 &sampleRate) {
    if(m_sampleRate == sampleRate)
        return;

    m_sampleRate = sampleRate;
    emit sampleRateChanged(sampleRate);
}

double KSound::amplitude() const {
    return m_amplitude;
}

void KSound::setAmplitude(double amplitude) {
    m_amplitude = amplitude;
}

int KSound::instanceCount() {
    return m_instanceCount;
}

KSound::KSound(bool play, QObject *parent) : QObject(parent) {
    setPlay(play);
    m_instanceCount++;
}

bool KSound::play() const {
    return m_play;
}

void KSound::setPlay(bool play) {
    if(m_play == play)
        return;

    overrideSetPlay();
    m_play = play;
    emit playChanged(play);
}
