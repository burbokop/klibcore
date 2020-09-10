#ifndef KVALUEHISTORY_H
#define KVALUEHISTORY_H

#include "kabstractvaluehistory.h"

#include <QElapsedTimer>
#include <QVector>


template<typename T>
class KValueHistory : public KAbstractValueHistory {
public:
    typedef typename QVector<QPair<time_t, T>>::size_type index_t;
private:

    QVector<QPair<time_t, T>> m_data = QVector<QPair<time_t, T>>();
    QElapsedTimer timer;
    time_t m_timeMark = 0;

    class history_unit_result_convertor {
        time_t m_t;
        T m_value;
    public:
        history_unit_result_convertor(const time_t &t, const T &value) { m_t = t; m_value = value; }
        operator QPair<time_t, T>() const { return QPair<time_t, T>(m_t, m_value); }
        operator T() const { return m_value; }
        operator QVariant() const { return QVariantMap { { "time", m_t }, {"value", m_value} }; }
    };
public:

    KValueHistory() { m_data.push_back({ 0, T() }); timer.start(); }
    index_t index(const time_t t0) const;
    index_t currentIndex(const time_t offset = 0) const { return index(timer.elapsed() + offset); };

    QVector<QPair<time_t, T>> data() const { return m_data; }

    bool wasActive(time_t t0, time_t t1) const;

    void updateState(time_t time, T value);
    void updateState(T value);

    time_t timeMark() const;
    void putTimeMark(const time_t &offset = 0);
    void setTimeMark(const time_t &timeMark);
    bool wasActiveFromTimeMark(const time_t &offset = 0);

    void clear() { m_data.clear(); };

    T average();

    T value(const time_t &mseconds) const {
        auto i = index(mseconds);
        if(i >= m_data.size())
            return T();
        return m_data[i].second;
    }

    inline virtual time_t currentTime() const override { return timer.elapsed(); }

    inline T currentValue(const time_t &offset = 0) const {
        return value(timer.elapsed() + offset);
    }

    template<typename result_t>
    result_t historySparseUnit(time_t t0, time_t t1, index_t count) const {
        assert(t0 < t1);
        result_t result;
        auto step = (t1 - t0) / count;
        for(time_t t = t0; t < t1; t += step) {
            result.push_back(history_unit_result_convertor(t, value(t)));
        }
        return result;
    }



    template<typename result_t>
    result_t historySparseUnit(time_t interval, index_t count) const {
        return historySparseUnit<result_t>(currentTime() - interval, currentTime(), count);
    }

    template<typename result_t>
    result_t historyUnit(time_t t0, time_t t1) const {
        assert(t0 < t1);
        result_t result;
        for(index_t i = index(t0), size = index(t1) + 1; i < size; ++i) {
            auto pair = m_data[i];
            result.push_back(history_unit_result_convertor(pair.first, pair.second));
        }
        return result;
    }

    template<typename result_t>
    result_t historyUnit(time_t interval) const {
        return historyUnit<result_t>(currentTime() - interval, currentTime());
    }

    virtual QVariantList historyUnit(time_t t0, time_t t1) const override {
        return historyUnit<QVariantList>(t0, t1);
    };

    virtual QVariantList historyUnit(time_t interval) const override {
        return historyUnit<QVariantList>(interval);
    };

    virtual QVariantList historySparseUnit(time_t t0, time_t t1, quint64 count) const override {
        return historySparseUnit<QVariantList>(t0, t1, count);
    };

    virtual QVariantList historySparseUnit(time_t interval, quint64 count) const override {
        return historySparseUnit<QVariantList>(interval, count);
    };
};


template<typename T>
T KValueHistory<T>::average() {
    if(m_data.size() <= 0)
        return T();

    T sum = 0;
    index_t i = 0;
    for(auto d : m_data) {
        sum += d.second;
        ++i;
    }
    return sum / i;
}


template<typename T>
typename KValueHistory<T>::time_t KValueHistory<T>::timeMark() const {
    return m_timeMark;
}

template<typename T>
void KValueHistory<T>::putTimeMark(const time_t &offset) {
    m_timeMark = timer.elapsed() + offset;
}

template<typename T>
void KValueHistory<T>::setTimeMark(const time_t &timeMark) {
    m_timeMark = timeMark;
}

template<typename T>
bool KValueHistory<T>::wasActiveFromTimeMark(const time_t &offset) {
    return wasActive(timeMark(), timer.elapsed() + offset);
}

template<typename T>
bool  KValueHistory<T>::wasActive(time_t t0, time_t t1) const {
    if ( t1 < t0 )
        qCritical("Warning: t1 < t0");

    if (m_data.isEmpty())
        return false;

    auto tmp = m_data.last();
    if (t0 > tmp.first)
        return tmp.second;

    qint32 foundIndex = index(t0);
    if (m_data[foundIndex].second)
        return true;

    if (++foundIndex >= m_data.size())
        return false;

    if ((m_data[foundIndex].first < t1) && m_data[foundIndex].second)
        return true;

    return false;
}

template<typename T>
typename KValueHistory<T>::index_t KValueHistory<T>::index(const time_t t0) const {
    typedef typename KValueHistory<T>::index_t i_t;

    i_t frontIndex = 0;
    i_t endIndex = m_data.size();
    i_t curIndex = (frontIndex + endIndex) / 2;
    while((endIndex - frontIndex) > 1) {
        if(m_data[curIndex].first > t0) {
            endIndex = curIndex;
            curIndex = (frontIndex + endIndex) / 2;
        } else {
            frontIndex = curIndex;
            curIndex = (frontIndex + endIndex) / 2;
        }
    }
    return frontIndex;
}

template<typename T>
void KValueHistory<T>::updateState(time_t time, T value) {
    if(m_data.size() > 0 && m_data.last().second == value)
        return;

    m_data.push_back(QPair<time_t, T>(time, value));
}

template<typename T>
void KValueHistory<T>::updateState(T value) {
    updateState(currentTime(), value);
}

#endif // KVALUEHISTORY_H
