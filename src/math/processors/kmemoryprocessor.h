#ifndef KMEMORYPROCESSOR_H
#define KMEMORYPROCESSOR_H

#include "ksignalprocessor.h"

#include <QElapsedTimer>
#include <QVector>

class KMemoryProcessor : public KSignalProcessor {
    K_OBJECT
    QVector<QPair<double, QElapsedTimer>> current;
    double fading;
public:
    KMemoryProcessor(double fading = 3.0);

    // SignalProcessor interface
protected:
    double signal(double value, int channel) override;    
    void reset() override;
};

#endif // KMEMORYPROCESSOR_H
