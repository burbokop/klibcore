#include "kmemoryprocessor.h"

KMemoryProcessor::KMemoryProcessor(double fading) {
    this->fading = fading;
}

double KMemoryProcessor::signal(double value, int channel) {
    if(channel >= current.size()) {
        current.resize(channel + 1);
        current[channel].second.start();
        current[channel].first = 0;
    }
    QPair<double, QElapsedTimer> &c = current[channel];
    if(c.first > 0) {
        c.first -= fading * c.second.restart() * 0.001 * c.first;
    }
    c.first = std::max(c.first, value);
    return c.first;
}

void KMemoryProcessor::reset() {
    current.clear();
}
