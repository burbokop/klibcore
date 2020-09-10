#include "ksoundmix.h"

#include <math.h>
#include <algorithm>

bool KSoundMix::average() const {
    return m_average;
}

void KSoundMix::setAverage(bool average) {
    m_average = average;
}

KSoundMix::KSoundMix(bool play, QObject *parent) : KSoundArray(play, parent) {}

double KSoundMix::signal(qint64 index) {
    double result = 0;
    double count = 0;
    for(KSound *sound : sounds()) {
        result += sound->volume(index);
        count++;
    }
    if(average() && !qFuzzyCompare(count, 0)) {
        result /= count;
    }
    result = std::min(result, 1.0);
    result = std::max(result, -1.0);
    return result;
}
