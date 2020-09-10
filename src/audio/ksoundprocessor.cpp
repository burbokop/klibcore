#include "ksoundprocessor.h"

#include <QtMath>

KSoundProcessor::KSoundProcessor(QObject *parent) : KSound(parent) {}

double KSoundProcessor::signal(qint64 index) {
    (void)index;
    auto m_frequency = 36000;

    if(m_frequency > 48000) {
    //    qCritical() << "m_frequency > 48000";
    }

    auto maxPosition = 48000;

    double value = 2 * M_PI * m_frequency * (it++ % maxPosition) / 48000 + 0;

    return process(qFastSin(value));
}
