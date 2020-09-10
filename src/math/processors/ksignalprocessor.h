#ifndef KSIGNALPROCESSOR_H
#define KSIGNALPROCESSOR_H

#include <list>
#include <src/kclassregistry.h>

/**
 * @brief The KSignalProcessor class
 *
 */
class KSignalProcessor {
    K_OBJECT
    std::list<std::pair<KSignalProcessor*, bool>> processors;
protected:
    virtual double signal(double value, int channel) { (void)channel; return value; };
    virtual void reset() {};
public:
    inline void resetSelf() { reset(); };
    inline void resetAll() { for(auto it = processors.begin(); it != processors.end(); ++it) { it->first->resetAll(); } reset(); };
    KSignalProcessor();
    double process(double value, int channel = 0);
    template<typename T>
    friend KSignalProcessor &operator<< (KSignalProcessor &s1, const T &s2);
    template<typename T>
    KSignalProcessor &another(const T &s2);
    KSignalProcessor *attachProcessor(KSignalProcessor *signal, bool interceptLife = false);

    virtual ~KSignalProcessor();
};

template<typename T>
KSignalProcessor &KSignalProcessor::another(const T &s2) {
    if constexpr (std::is_same<T, typename std::remove_pointer<T>::type>::value) {
        return *attachProcessor(new T(s2), true);
    } else {
        return *attachProcessor(s2);
    }
}

template<typename T>
KSignalProcessor &operator<<(KSignalProcessor &s1, const T &s2) {
    if constexpr (std::is_same<T, typename std::remove_pointer<T>::type>::value) {
        return *s1.attachProcessor(new T(s2), true);
    } else {
        return *s1.attachProcessor(s2);
    }
}



#endif // KSIGNALPROCESSOR_H
