#include "kgraphics_test.h"
#include <QAudioOutput>
#include <QTimer>
#include <math.h>
#include <src/audio/kaudiodevice.h>
#include <src/audio/ksoundprocessor.h>
#include <src/math/processors/kmemoryprocessor.h>
#include <src/math/processors/knoisegenerator.h>
#include <src/math/processors/kqualitydeteriorator.h>

KGraphics_Test::KGraphics_Test(QObject *parent) : QObject(parent) {
    processor << KNoiseGenerator(0.4);

    connect(this, &KGraphics_Test::boolValueChanged, this, [this](bool value) {
        boolHistory.updateState(value);
    });
    //connect(this, &KGraphics_Test::doubleValueChanged, this, [this](double value) {
    //
    //});

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        auto value = amplitude() * std::sin(doubleHistory.currentTime() * freq() * 0.001) * std::sin(doubleHistory.currentTime() * 1 * 0.001);
        doubleHistory.updateState(value);
        derivetiveHistory.updateState(processor.process(value));
    });
    timer->start(20);
}

void KGraphics_Test::installMonitor(KHistoryMonitor *mon) {
    mon->addHistory(&boolHistory, QPen("#ff8800"), "pin", KHistoryMonitor::Discrete);
    mon->addHistory(&doubleHistory, QPen("#777777"), "val", KHistoryMonitor::Uninterrupted);
    mon->addHistory(&derivetiveHistory, QPen(QColor("#ff00ff"), 1), "der", KHistoryMonitor::Discrete);
}
