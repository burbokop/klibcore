#include "knoisegenerator.h"

#include <QDateTime>
#include <QRandomGenerator>

KNoiseGenerator::KNoiseGenerator(double coeficient, double delay, Mode mode) {
    m_coeficient = coeficient;
    m_mode = mode;
    cnt = delay;
}

QRandomGenerator* KNoiseGenerator::gen = new QRandomGenerator(static_cast<unsigned>(QDateTime::currentDateTime().currentMSecsSinceEpoch()));

double KNoiseGenerator::signal(double value, int channel) {
    typedef std::vector<ChannelState>::size_type vint;
    auto c = static_cast<vint>(channel);
    if(c >= channelStateArray.size()) {
        channelStateArray.resize(c + 1);
        for(vint i = 0 ; i < channelStateArray.size(); ++i) {
            channelStateArray[i].i = commonRandom() % cnt;
            if(m_mode == Percent) {
                channelStateArray[i].noise = percentRandom();
            } else {
                channelStateArray[i].noise = signalRandom();
            }
        }
    }

    if(channelStateArray[channel].i-- <= 0) {
        channelStateArray[channel].i = commonRandom() % cnt;
        if(m_mode == Percent) {
            channelStateArray[channel].noise = percentRandom();
        } else {
            channelStateArray[channel].noise = signalRandom();
        }
    }
    return value + channelStateArray[channel].noise * m_coeficient;
}

unsigned KNoiseGenerator::commonRandom() {
    return static_cast<unsigned>(gen->generate());
}

double KNoiseGenerator::percentRandom() {
    return static_cast<double>(commonRandom()) / static_cast <double>(gen->max());
}

double KNoiseGenerator::signalRandom() {
    return percentRandom() * 2 - 1;
}

void KNoiseGenerator::reset() {
    return channelStateArray.clear();
}
