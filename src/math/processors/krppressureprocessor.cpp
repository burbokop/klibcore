
#include "krppressureprocessor.h"

#include <math.h>

QVector<double> KRpPressureProcessor::sweep() const {
    return m_sweep;
}

void KRpPressureProcessor::internalProceed() {
    auto it = pressures.begin();
    while (it != pressures.end()) {
        if(it->isReadyDelete()) {
            it = pressures.erase(it);
        } else {
            if(it->type() == Pressure::Type::Reverberation) {
                for(int j = 0; j < m_sweep.size(); ++j) {
                    m_sweep[j] = it->pressure() * kmath->gaus(it->elapsed() / 100);
                }
            } else if(mode() == SpatialProcessing) {
                int velocityChannel = static_cast<int>(kmath->dmap(it->velocity(), maxVelocity(), minVelocity(), 0, channalCount() - 1));
                int index = it->xn() * channalCount() + velocityChannel;
                if(index < m_sweep.size() && index >= 0) {
                    m_sweep[index] = it->pressure();
                }
            } else if(mode() == FrequencyProcessing) {
                int index = static_cast<int>(kmath->dmap(it->velocity(), minVelocity(), maxVelocity(), 0, channalCount() - 1));
                if(index >= 0 && index < m_sweep.size()) {
                    m_sweep[index] += it->pressure();
                }
            }
            ++it;
        }
    }

    for(int i = 0; i < m_sweep.size(); ++i) {
        m_sweep[i] = process(m_sweep[i], i);
    }
}

KRpPressureProcessor::KRpPressureProcessor() {}

void KRpPressureProcessor::addPressure(double angle, double intensity, double radialVelocity, double emissionTime) {
    auto function = [](double value) {
        return qFuzzyCompare(value, 0) ? 1.0 : qAbs(sin(value) / value);
    };

    auto startPoint = xnRotation() - (xnShiftAngle() * (xnCount() - 1)) * 0.5 + vesselRotation();
    for(int i = 0; i < xnCount(); ++i) {
        double currentXnAngle = kmath->constrainDegrees(startPoint + xnShiftAngle() * i);
        double pressure = function(kmath->degreesDifference(angle, currentXnAngle) * 90 / 6 * M_PI / 180) * intensity;
        pressures.push_back(Pressure(i, pressure, radialVelocity, emissionTime));
    }
}

void KRpPressureProcessor::proceed() {
    if(mode() == SpatialProcessing) {
        m_sweep = QVector<double>(channalCount() * xnCount());
    } else if(mode() == FrequencyProcessing) {
        m_sweep = QVector<double>(channalCount());
    }
    internalProceed();
}

