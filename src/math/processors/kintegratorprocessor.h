#ifndef KINTEGRATORPROCESSOR_H
#define KINTEGRATORPROCESSOR_H

#include "ksignalprocessor.h"
#include <vector>

class KIntegratorProcessor : public KSignalProcessor {
    K_OBJECT
    double alpha;

    struct ChannelState {
        double lastY;
        bool frst = true;
    };

    std::vector<ChannelState> channelStateArray;
public:
    KIntegratorProcessor(double alpha = 0.9);

    // SignalProcessor interface
protected:
    double signal(double value, int channel) override;
    void reset() override;
};

#endif // KINTEGRATORPROCESSOR_H
