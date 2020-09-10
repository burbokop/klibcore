#ifndef KNOISEGENERATOR_H
#define KNOISEGENERATOR_H

#include "ksignalprocessor.h"
#include <vector>

class QRandomGenerator;
class KNoiseGenerator : public KSignalProcessor {
    K_OBJECT
public:
    enum Mode {
        Signal,
        Percent
    };
private:

    double m_coeficient = 0.05;
    int cnt = 32;
    static QRandomGenerator* gen;
    Mode m_mode;

    struct ChannelState {
        int i = 0;
        double noise = percentRandom();
    };

    std::vector<ChannelState> channelStateArray;
public:
    KNoiseGenerator(double coeficient = 0.05, double delay = 32, Mode mode = Percent);

    // SignalProcessor interface
protected:
    double signal(double value, int channel) override;
    void reset() override;
public:
    static unsigned commonRandom();
    static double percentRandom();
    static double signalRandom();


};

#endif // KNOISEGENERATOR_H
