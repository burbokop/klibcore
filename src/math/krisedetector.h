#ifndef KRISEDETECTOR_H
#define KRISEDETECTOR_H


class KRiseDetector {
    bool oldState = false;
public:
    inline bool check(bool newState) {
        auto tmp = oldState;
        oldState = newState;
        return !tmp && newState;
    }
};

#endif // KRISEDETECTOR_H
