#include "ksysinfo.h"

#include <QSysInfo>
#include <QTimer>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define __K_WINDOWS__
#endif

#ifdef __K_WINDOWS__
#include <windows.h>
#endif



KSysInfo::KSysInfo(QObject *parent) : QObject(parent) {
    setMachineUniqueId(QSysInfo::machineUniqueId());
    setMachineHostName(QSysInfo::machineHostName());

#ifdef __K_WINDOWS__
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        SYSTEM_POWER_STATUS status;
        if(GetSystemPowerStatus(&status)) {
            setBatteryLevel(static_cast<double>(status.BatteryLifePercent) * 0.01);
            setBatteryLifeTime(status.BatteryLifeTime);
            setBatteryFullLifeTime(status.BatteryFullLifeTime);
            setBatteryReserved1(status.Reserved1);
            setBatteryFlag(status.BatteryFlag);
            setACLineStatus(status.ACLineStatus);
        }
    });
    timer->start(1000);
#endif

}

