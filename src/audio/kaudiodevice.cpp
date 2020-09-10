#include "kaudiodevice.h"

#include <src/math/kmath.h>

#include <QAudioDeviceInfo>

QAudioFormat KAudioDevice::format() const {
    return m_format;
}

KAudioDevice::KAudioDevice(QObject *parent) : QIODevice(parent) {
    m_format = generateFormat();
}

QAudioFormat KAudioDevice::generateFormat() {
    QAudioFormat audioFormat;
    audioFormat.setSampleRate(static_cast<int>(48000));
    audioFormat.setChannelCount(1);
    audioFormat.setSampleSize(16);
    audioFormat.setCodec("audio/pcm");
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    audioFormat.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo deviceInfo((QAudioDeviceInfo::defaultOutputDevice()));
    if(!deviceInfo.isFormatSupported(audioFormat))
        throw "Raw audio format not supported by backend, cannot play audio.";

    return audioFormat;
}

qint64 KAudioDevice::readData(char *data, qint64 len) {
    constexpr auto maxReadCount = 48000;
    constexpr auto maxAmplitude = 32768;
    if (len > maxReadCount) len = maxReadCount;
    auto data16 = reinterpret_cast<qint16*>(data);
    for (qint64 i = 0; i < len / 2; ++i) {
        data16[i] = static_cast<qint16>(KMath::instance()->dmap(process(0), -1, 1, -maxAmplitude, maxAmplitude));
    }
    return static_cast<qint64>(len / 2) * 2;
}

qint64 KAudioDevice::writeData(const char *data, qint64 len) {
    Q_UNUSED(data)
    Q_UNUSED(len)
    return 0;
}


