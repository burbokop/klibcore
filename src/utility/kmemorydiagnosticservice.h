#ifndef KMEMORYDIAGNOSTICSERVICE_H
#define KMEMORYDIAGNOSTICSERVICE_H


#include <QObject>
#include "kvaluehistory.h"
#include <src/math/processors/kdifferentiator.h>

/**
 * @brief The KMemoryDiagnosticService class provide calculation statistic of memory usage by application.
 *
 * @details This class is not compleated now. It may be removed and is <b>DEPRECATED</b>
 */
class KMemoryDiagnosticService : public QObject {
    Q_OBJECT


    KDifferentiator vmDifferentiator;
    KDifferentiator rssDifferentiator;
    KValueHistory<double> vmHistory;
    KValueHistory<double> rssHistory;
    KValueHistory<double> vmDerivativeHistory;
    KValueHistory<double> rssDerivativeHistory;

    static void process_mem_usage(double& vm_usage, double& resident_set);
public:
    struct Memory { double vm = 0; double rss = 0; };

    static double runtimeVM();
    static double runtimeRSS();
    inline static Memory runtimeMemoryUsage() { double vm, rss; process_mem_usage(vm, rss); return { vm, rss }; }

    explicit KMemoryDiagnosticService(QObject *parent = nullptr);

    Memory average();
    Memory derivativeAverage();

    void restart();
public slots:
    QVariant vmHistoryUnit(qint64 interval, qint64 count);
    QVariant rssHistoryUnit(qint64 interval, qint64 count);

};

#endif // KMEMORYDIAGNOSTICSERVICE_H
