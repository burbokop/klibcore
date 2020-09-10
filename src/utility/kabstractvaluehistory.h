#ifndef KABSTRACTVALUEHISTORY_H
#define KABSTRACTVALUEHISTORY_H

#include <QVariant>

/**
 * @brief The KAbstractValueHistory interface summarizes value history classes and is used for visualization them in qml (see KHistoryMonitor).
 */
class KAbstractValueHistory {
public:
    typedef qint64 time_t;

    KAbstractValueHistory();

    /**
     * @brief currentTime - getter of current time since instance has created
     * @return time_t (aka qint64)
     */
    virtual time_t currentTime() const = 0;
    /**
     * @brief historyUnit function returns part of history form time <b>t0</b> to time <b>t1</b>
     * @param t0
     * @param t1
     * @return QVariantList with part of history
     * @details This function returns all history points from time <b>t0</b> to time <b>t1</b> so be carefuly,
     * if your value is changing often calling this function can take a long time.
     * Precision of result is the same as precision of origin value history, so if you want maximum precision and you don't care about time, use this function.
     * @note you shoold use time recieved from KAbstractValueHistory::currentTime function, otherwise undefined behaviour
     */
    virtual QVariantList historyUnit(time_t t0, time_t t1) const = 0;
    /**
     * @brief historyUnit overload do the same as <b>historyUnit(time_t, time_t)</b> but use other time definition
     * @param interval - (t0 = currentTime - interval, t1 = currentTime)
     * @return QVariantList with part of history
     * @note you shoold use time recieved from KAbstractValueHistory::currentTime function, otherwise undefined behaviour
     */
    virtual QVariantList historyUnit(time_t interval) const = 0;
    /**
     * @brief historySparseUnit function returns part of history form time <b>t0</b> to time <b>t1</b> and with a given number of points
     * @param t0
     * @param t1
     * @param count - points count in result list
     * @return QVariantList with part of history
     * @details instead of KAbstractValueHistory::historyUnit this function decrease density of points so that it contains <b>count</b> points.
     * This function is used if your value is changing often and you do not need so high precision, but want high speed.
     * @note you shoold use time recieved from KAbstractValueHistory::currentTime function, otherwise undefined behaviour
     */
    virtual QVariantList historySparseUnit(time_t t0, time_t t1, quint64 count) const = 0;
    /**
     * @brief historySparseUnit overload do the same as <b>historySparseUnit(time_t, time_t, quint64)</b> but use other time definition
     * @param interval - (t0 = currentTime - interval, t1 = currentTime)
     * @param count - points count in result list
     * @return QVariantList with part of history
     * @note you shoold use time recieved from KAbstractValueHistory::currentTime function, otherwise undefined behaviour
     */
    virtual QVariantList historySparseUnit(time_t interval, quint64 count) const = 0;

    virtual ~KAbstractValueHistory();
};

#endif // KABSTRACTVALUEHISTORY_H
