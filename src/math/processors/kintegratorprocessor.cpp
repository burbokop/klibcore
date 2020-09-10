#include "kintegratorprocessor.h"

KIntegratorProcessor::KIntegratorProcessor(double alpha) {
    this->alpha = alpha;
}

double KIntegratorProcessor::signal(double value, int channel) {
    auto c = static_cast<std::vector<ChannelState>::size_type>(channel);
    if(c >= channelStateArray.size())
        channelStateArray.resize(c + 1);

    if (channelStateArray[channel].frst) {
        channelStateArray[channel].frst = false;
        return (channelStateArray[channel].lastY = value);
    }
    return (channelStateArray[channel].lastY = alpha * channelStateArray[channel].lastY + (1 - alpha) * value);
}


void KIntegratorProcessor::reset() {
    channelStateArray.clear();
}
