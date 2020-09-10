#ifndef KHISTORYMONITOR_H
#define KHISTORYMONITOR_H

#include "kpainteditem.h"
#include <QPen>
#include <src/kmacro.h>
#include <src/math/processors/kintegratorprocessor.h>
#include <src/utility/kabstractvaluehistory.h>

/**
 * @brief The KHistoryMonitor class provides display number value hystory as chart
 * @details This class use KAbstractValueHistory as model for displaying.
 * There is available diplaying more then one value hystory
 *
 * \n
 * PROPERTIES:
 *
 * | modyfier | type   | name           | description                                            |
 * | -------- | ------ | -------------- | ------------------------------------------------------ |
 * | writable | int    | updateInterval | update interval in miliseconds                         |
 * | writable | qint64 | timeWidth      | time delta from some time in the past and current time |
 * | writable | double | min            | minimum displayed value (minimum y)                    |
 * | writable | double | max            | maximum displayed value (maximum y)                    |
 *
 * \n
 */

class KHistoryMonitor : public KPaintedItem {
    Q_OBJECT
    K_QML_TYPE(KHistoryMonitor)
    K_AUTO_PROPERTY(int, updateInterval, updateInterval, setUpdateInterval, updateIntervalChanged, 50)
    K_AUTO_PROPERTY(qint64, timeWidth, timeWidth, setTimeWidth, timeWidthChanged, 10000)
    K_AUTO_PROPERTY(double, min, min, setMin, minChanged, -0.5)
    K_AUTO_PROPERTY(double, max, max, setMax, maxChanged, 1.5)

public:
    /**
     * @brief The GraphStyle enum says to monitor what algorythm for diplaying it should use.
     */
    enum GraphStyle {
        /**
         * Value is displayed as if it is a dicrete value (without smoothing and dilution)
         */
        Discrete,
        /**
         * Value is displayed as if it is a uninterrupted analog value (enabled special optimisation)
         */
        Uninterrupted,
        /**
         * The same as Uninterrupted but with smoothing
         */
        UninterruptedWithIntegrator,
        /**
         * Needed for displaying amazing picture
         */
        Distortion
    };

    struct Record {
        KAbstractValueHistory *history = nullptr;
        QPen pen;
        QString title;
        GraphStyle style = Discrete;
    };
private:
    KIntegratorProcessor integrator;


    QList<Record> records;
    QMap<KAbstractValueHistory*, QVector<Record>::size_type> channels;

    void drawChart(QPainter *painter, Record r, quint64 channel);
public:
    KHistoryMonitor(QQuickItem *parent = nullptr);

    // QQuickPaintedItem interface
public:
    void paint(QPainter *painter) override;

public slots:
    /**
     * @brief addHistory - adds history and gets some options for displaying this history (history monitor does not intercept life of history)
     * @param history - pointer to KAbstractValueHistory instance
     * @param pen
     * @param title - title that will be displayed
     * @param style - see KHistoryMonitor::GraphStyle
     */
    void addHistory(KAbstractValueHistory *history, QPen pen = QPen("#ff8000"), QString title = QString(), GraphStyle style = Discrete);
    /**
     * @brief removeHistory - removes history if current is added
     * @param history - pointer to KAbstractValueHistory instance we want to remove
     * @return true if removing is succesfully
     */
    bool removeHistory(KAbstractValueHistory *history);
};

inline bool operator ==(const KHistoryMonitor::Record &r1, const KHistoryMonitor::Record &r2) { return r1.history == r2.history; }

#endif // KHISTORYMONITOR_H
