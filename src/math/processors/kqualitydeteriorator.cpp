#include "kqualitydeteriorator.h"

#include <math.h>

KQualityDeteriorator::KQualityDeteriorator(double count) {
    m_count = count;
}

double KQualityDeteriorator::signal(double value, int channel) {
    (void)channel;
    return std::floor(m_count * value) / m_count;
}
