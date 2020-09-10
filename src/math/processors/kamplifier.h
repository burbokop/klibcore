#ifndef KAMPLIFIER_H
#define KAMPLIFIER_H

#include "ksignalprocessor.h"
#include <src/kmacro.h>

class KAmplifier : public KSignalProcessor {
    K_OBJECT
    K_AUTO_MEMBER(double, coeficient, coeficient, setCoeficient, 1)
public:
    KAmplifier(double coeficient = 1);

    // KSignalProcessor interface
protected:
    double signal(double value, int channel) override;
};

#endif // KAMPLIFIER_H
