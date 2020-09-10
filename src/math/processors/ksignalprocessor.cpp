#include "ksignalprocessor.h"

KSignalProcessor::KSignalProcessor() {}

double KSignalProcessor::process(double value, int channel) {
    double last = 0;
    bool hasLast = false;
    for(auto proc : processors) {
        if(hasLast) {
            last = proc.first->process(last, channel);
        } else {
            last = proc.first->process(value, channel);
        }
        hasLast = true;
    }

    if(hasLast) {
        return signal(last, channel);
    } else {
        return signal(value, channel);
    }
}

KSignalProcessor::~KSignalProcessor() {
    for(auto p : processors) {
        if(p.second)
            delete p.first;
    }
}


KSignalProcessor *KSignalProcessor::attachProcessor(KSignalProcessor *signal, bool interceptLife) {
    processors.push_front({ signal, interceptLife });
    return this;
}
