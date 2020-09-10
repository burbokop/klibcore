#include "kaudio_test.h"

#include <src/audio/kaudiodevice.h>
#include <src/audio/ksoundprocessor.h>

#include <src/math/processors/kintegratorprocessor.h>
#include <src/math/processors/koscillator.h>
#include <src/math/processors/kqualitydeteriorator.h>

#include <QAudioOutput>

KAudio_Test::KAudio_Test(QObject *parent) : QObject(parent) {
    audioDevice.attachProcessor(&oscillator);


    QAudioOutput *audioOutput = new QAudioOutput(audioDevice.format(), this);
    audioDevice.open(QIODevice::ReadOnly);
    //audioOutput->start(&audioDevice);
    Q_UNUSED(audioOutput);
    connect(this, &KAudio_Test::amplitudeChanged, this, [this](auto value) {
        oscillator.setAmplitude(value);
    });
    connect(this, &KAudio_Test::frequencyChanged, this, [this](auto value) {
        oscillator.setFrequency(value);
    });
    connect(this, &KAudio_Test::phaseChanged, this, [this](auto value) {
        oscillator.setPhase(value);
    });
}
