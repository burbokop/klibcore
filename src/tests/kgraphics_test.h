#ifndef KGRAPHICS_TEST_H
#define KGRAPHICS_TEST_H

#include <QObject>
#include <src/graphics/khistorymonitor.h>
#include <src/kmacro.h>
#include <src/math/processors/kdifferentiator.h>
#include <src/utility/kvaluehistory.h>

class KGraphics_Test : public QObject {
    Q_OBJECT
    K_QML_TYPE(KGraphics_Test)
    K_AUTO_PROPERTY(bool, boolValue, boolValue, setBoolValue, boolValueChanged, false)
    K_AUTO_PROPERTY(double, amplitude, amplitude, setAmplitude, amplitudeChanged, 0)
    K_AUTO_PROPERTY(double, freq, freq, setFreq, freqChanged, 1)
    K_AUTO_PROPERTY(double, doubleValue, doubleValue, setDoubleValue, doubleValueChanged, 0)
    KValueHistory<bool> boolHistory;
    KValueHistory<double> doubleHistory;
    KValueHistory<double> derivetiveHistory;
    KSignalProcessor processor;
public:
    explicit KGraphics_Test(QObject *parent = nullptr);

signals:

public slots:
    void installMonitor(KHistoryMonitor *mon);
};

#endif // KGRAPHICS_TEST_H
