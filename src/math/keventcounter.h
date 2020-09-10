#ifndef KEVENTCOUNTER_H
#define KEVENTCOUNTER_H

#include "krisedetector.h"

class KEventCounter {
    int count = 0;
    KRiseDetector riseDetector;
    int m_ncnt = 1;
public:
    KEventCounter(int ncnt = 1);

    inline bool check(bool newState) {
        if(riseDetector.check(newState))
            count++;

        if(count == m_ncnt) {
            count = 0;
            return true;
        }
        return false;
    }
};

#endif // KEVENTCOUNTER_H
