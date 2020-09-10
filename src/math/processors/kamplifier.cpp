#include "kamplifier.h"

KAmplifier::KAmplifier(double coeficient) {
    m_coeficient = coeficient;
}


double KAmplifier::signal(double value, int channel) {
    (void)channel;
    return value * coeficient();
}
