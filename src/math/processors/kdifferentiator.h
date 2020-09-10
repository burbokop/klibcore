#ifndef KDIFFERENTIATOR_H
#define KDIFFERENTIATOR_H

#include "ksignalprocessor.h"

#include <QElapsedTimer>
#include <QVector>

class KDifferentiator : public KSignalProcessor {
    K_OBJECT
    QVector<QPair<double, QElapsedTimer>> channelData;
public:
    KDifferentiator();

    // KSignalProcessor interface
protected:
    double signal(double value, int channel) override;
    void reset() override;
};

#endif // KDIFFERENTIATOR_H
