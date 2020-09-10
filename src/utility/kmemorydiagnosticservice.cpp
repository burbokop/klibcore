#include "kmemorydiagnosticservice.h"

#include <QTimer>
#include <fstream>
#include <unistd.h>


KMemoryDiagnosticService::KMemoryDiagnosticService(QObject *parent) : QObject(parent) {
    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, [this]() {
        auto mem = runtimeMemoryUsage();
        vmHistory.updateState(mem.vm);
        rssHistory.updateState(mem.rss);
        vmDerivativeHistory.updateState(vmDifferentiator.process(mem.vm));
        rssDerivativeHistory.updateState(rssDifferentiator.process(mem.rss));
    });
    updateTimer->start(1000);
}

KMemoryDiagnosticService::Memory KMemoryDiagnosticService::average() {
    return { vmHistory.average(), rssHistory.average() };
}

KMemoryDiagnosticService::Memory KMemoryDiagnosticService::derivativeAverage() {
    return { vmDerivativeHistory.average(), rssDerivativeHistory.average() };
}

void KMemoryDiagnosticService::restart() {
    vmDifferentiator.resetSelf();
    rssDifferentiator.resetSelf();
    vmHistory.clear();
    rssHistory.clear();
    vmDerivativeHistory.clear();
    rssDerivativeHistory.clear();
}

QVariant KMemoryDiagnosticService::vmHistoryUnit(qint64 interval, qint64 count) {
    return vmHistory.historySparseUnit<QVariantList>(interval, count);
}

QVariant KMemoryDiagnosticService::rssHistoryUnit(qint64 interval, qint64 count) {
    return rssHistory.historySparseUnit<QVariantList>(interval, count);
}

void KMemoryDiagnosticService::process_mem_usage(double& vm_usage, double& resident_set) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    // Winda
#else
    vm_usage = 0.0;
    resident_set = 0.0;
    unsigned long vsize;
    long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
            >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
            >> ignore >> ignore >> vsize >> rss;
    }

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_kb;
#endif
}

double KMemoryDiagnosticService::runtimeVM() {
    double vm, rss;
    process_mem_usage(vm, rss);
    return vm;
}

double KMemoryDiagnosticService::runtimeRSS() {
    double vm, rss;
    process_mem_usage(vm, rss);
    return rss;
}
