#ifndef KQUALITYDETERIORATOR_H
#define KQUALITYDETERIORATOR_H

#include "ksignalprocessor.h"

class KQualityDeteriorator : public KSignalProcessor {
    K_OBJECT
    double m_count = 1;
public:
    KQualityDeteriorator(double count = 1);

    // SignalProcessor interface

protected:
    double signal(double value, int channel) override;
};

#endif // KQUALITYDETERIORATOR_H
