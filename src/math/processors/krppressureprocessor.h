#ifndef XNPRESSURECONVERTOR_H
#define XNPRESSURECONVERTOR_H

#include "ksignalprocessor.h"
#include <QElapsedTimer>
#include <src/kmacro.h>
#include <src/math/kmath.h>


struct KRpPressureProcessor : public KSignalProcessor {
    K_OBJECT
    enum Mode { SpatialProcessing, FrequencyProcessing };
    class Pressure {
    public:
        enum Type { Default, Reverberation };
    private:
        static inline int nextId = 0;
        QElapsedTimer timer;
        K_AUTO_MEMBER(int, xn, xn, seXn, -1)
        K_AUTO_MEMBER(double, pressure, pressure, setPressure, 0.0)
        K_AUTO_MEMBER(double, velocity, velocity, setVelocity, 0.0)
        K_AUTO_MEMBER(double, emissionTime, emissionTime, setEmissionTime, 0.0)
        K_AUTO_MEMBER(Type, type, type, setType, Default);
        int id = -1;
    public:
        Pressure(int xn, double pressure, double velocity, double emissionTime, Type type = Default)
            : m_xn(xn),
              m_pressure(pressure),
              m_velocity(velocity),
              m_emissionTime(emissionTime),
              m_type(type),
              id(nextId++)
        { timer.start(); }
        Pressure(Type type = Default)
            : m_type(type),
              id(nextId++)
        { timer.start(); }
        inline qint64 elapsed() const { return timer.elapsed(); }
        inline bool isReadyDelete() const { return elapsed() > emissionTime(); }
        inline friend bool operator ==(Pressure& pressure1, const Pressure& pressure2) { return pressure1.id == pressure2.id; }
    };

    K_AUTO_MEMBER(double, xnRotation, xnRotation, setXnRotation, 0)
    K_AUTO_MEMBER(double, vesselRotation, vesselRotation, setVesselRotation, 0)
    K_AUTO_MEMBER(double, xnShiftAngle, xnShiftAngle, setXnShiftAngle, 0)
    K_AUTO_MEMBER(double, minVelocity, minVelocity, setMinVelocity, 0)
    K_AUTO_MEMBER(double, maxVelocity, maxVelocity, setMaxVelocity, 0)
    K_AUTO_MEMBER(double, noiseAmplitude, noiseAmplitude, setNoiseAmplitude, 1)
    K_AUTO_MEMBER(int, xnCount, xnCount, setXnCount, 0)
    K_AUTO_MEMBER(int, channalCount, channalCount, setChannalCount, 0)
    K_INCLUDE_MATH
    K_AUTO_MEMBER(Mode, mode, mode, setMode, SpatialProcessing)

    QList<Pressure> pressures;

    QVector<double> m_sweep;

    void internalProceed();
public:
    explicit KRpPressureProcessor();
    void addPressure(double angle, double intensity, double radialVelocity, double emissionTime);
    void proceed();
    QVector<double> sweep() const;

signals:
    void pressureAdded(QVariant value);
public slots:
};

#endif // XNPRESSURECONVERTOR_H
