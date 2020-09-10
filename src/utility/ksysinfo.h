#ifndef KSYSINFO_H
#define KSYSINFO_H

#include <QObject>
#include <src/kmacro.h>

class KSysInfo : public QObject {
    Q_OBJECT
    K_PRIVATE_SINGLETON(KSysInfo)
    K_QML_SINGLETON(KSysInfo)

    K_READONLY_PROPERTY(QByteArray, machineUniqueId, machineUniqueId, setMachineUniqueId, machineUniqueIdChanged, QByteArray())
    K_READONLY_PROPERTY(QString, machineHostName, machineHostName, setMachineHostName, machineHostNameChanged, QString())
    K_READONLY_PROPERTY(double, batteryLevel, batteryLevel, setBatteryLevel, batteryLevelChanged, 1)
    K_READONLY_PROPERTY(int, batteryLifeTime, batteryLifeTime, setBatteryLifeTime, batteryLifeTimeChanged, 0)
    K_READONLY_PROPERTY(int, batteryFullLifeTime, batteryFullLifeTime, setBatteryFullLifeTime, batteryFullLifeTimeChanged, 0)
    K_READONLY_PROPERTY(quint8, batteryReserved1, batteryReserved1, setBatteryReserved1, batteryReserved1Changed, 0)
    K_READONLY_PROPERTY(quint8, batteryFlag, batteryFlag, setBatteryFlag, batteryFlagChanged, 0)
    K_READONLY_PROPERTY(quint8, ACLineStatus, ACLineStatus, setACLineStatus, ACLineStatusChanged, 0)
public:
    explicit KSysInfo(QObject *parent = nullptr);

signals:

};

#endif // KSYSINFO_H
