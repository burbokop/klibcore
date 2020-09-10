#include "kdifferentiator.h"

#include <src/klibinfo.h>

KDifferentiator::KDifferentiator() {}

double KDifferentiator::signal(double value, int channel) {
    auto casted_channel = static_cast<QVector<QPair<double, QElapsedTimer>>::size_type>(channel);
    if(casted_channel >= channelData.size()) {
        channelData.resize(casted_channel + 1);
        channelData[casted_channel].second.restart();
        channelData[casted_channel].first = value;
        return 0;
    }

    QPair<double, QElapsedTimer> &c = channelData[casted_channel];

    const double deltaValue = value - c.first;
    const double deltaTime = static_cast<double>(c.second.restart()) * 0.001;
    c.first = value;
    return KCompareEngine<double>::compare(deltaTime, 0) ? 0 : (deltaValue / deltaTime);
}


void KDifferentiator::reset() {
    channelData.clear();
}
