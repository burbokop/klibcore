#ifndef KAUDIO_TEST_H
#define KAUDIO_TEST_H

#include <QObject>
#include <src/audio/kaudiodevice.h>
#include <src/kmacro.h>
#include <src/math/processors/koscillator.h>

class KAudio_Test : public QObject {
    Q_OBJECT
    K_QML_TYPE(KAudio_Test)

    K_AUTO_PROPERTY(double, amplitude, amplitude, setAmplitude, amplitudeChanged, 1)
    K_AUTO_PROPERTY(double, frequency, frequency, setFrequency, frequencyChanged, 32000)
    K_AUTO_PROPERTY(double, phase, phase, setPhase, phaseChanged, 0)

    KAudioDevice audioDevice;
    KOscillator oscillator;

public:
    explicit KAudio_Test(QObject *parent = nullptr);

signals:

};

#endif // KAUDIO_TEST_H
