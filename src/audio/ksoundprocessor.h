#ifndef KSOUNDPROCESSOR_H
#define KSOUNDPROCESSOR_H

#include <src/math/processors/ksignalprocessor.h>
#include "ksound.h"

class KSoundProcessor : public KSound, public KSignalProcessor {
    int it = 0;
public:
    KSoundProcessor(QObject *parent = nullptr);

    // KSound interface
protected:
    double signal(qint64 index) override;
};

#endif // KSOUNDPROCESSOR_H
