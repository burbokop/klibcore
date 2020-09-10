#ifndef KMATH_H
#define KMATH_H

#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>
#include <QVector>
#include <QVector2D>

#include <src/kmacro.h>

#define K_INCLUDE_MATH \
private: \
    const static inline KMath *kmath = KMath::instance();

class KMath : public QObject {
    Q_OBJECT
    K_SINGLETON(KMath)
    K_QML_SINGLETON(KMath)
    KMath(QObject *parent = nullptr);
public:
    template<typename T>
    void bubbleSort(QVector<T> *array) const;
    template<typename container_t>
    QVector<quint64> customContainerIndices(container_t container) const;

    template<typename container_t>
    typename container_t::value_type customContainerAverage(container_t container) const {
        typedef typename container_t::value_type item_t;
        if(container.size() <= 0)
            return item_t();

        item_t sum = item_t();
        quint64 i = 0;
        for(auto c :container) {
            sum += c;
            i++;
        }
        return sum / i;
    }    
public slots:
    float constrainAngle(float value) const;
    float constrainDegrees(float value) const;
    double constrainDegrees(double value) const;
    float determinant(QVector2D vector1, QVector2D vector2) const;
    float getAngle(QVector2D vector1, QVector2D vector2) const;
    float getDegrees(QVector2D vector1, QVector2D vector2) const;
    bool direction(float dstAngle, float angle) const;
    bool direction(double dstAngle, double angle) const;
    float distance(float dstAngle, float angle) const;

    float degreesDistance(float angle1, float angle2) const;
    float degreesDifference(float angle1, float angle2) const;
    double degreesDistance(double angle1, double angle2) const;
    double degreesDifference(double angle1, double angle2) const;

    float map(float value, float inMin, float inMax, float outMin, float outMax) const;
    double dmap(double value, double inMin, double inMax, double outMin, double outMax) const;
    double limitValue(double value, double min, double max) const;
    double limitedMap(double value, double inMin, double inMax, double outMin, double outMax) const;
    double sigm(double value) const;
    double gaus(double value) const;
    QVector<double> bubbleSort(const QVector<double> &array) const;
    QVector<quint64> vectorIndices(const QVector<double> &vector) const;
    double random() const;
    double randomStep() const;
    double toKnots(double value) const;
    double fromKnots(double value) const;
    int toTop(double value) const;
    QVector<double> resampling(const QVector<double> &input, int sizeMultiplier) const;
    QVector<double> integrate(QVector<double> input, double alpha) const;
    QVector<double> smooth(const QVector<double> &input, double alpha, int sizeMultiplier) const;
};

template<typename T>
void KMath::bubbleSort(QVector<T> *array) const {
    T temp;
    auto&& size = array->size();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array->operator[](j) > array->operator[](j + 1)) {
                temp = array->operator[](j);
                array->operator[](j) = array->operator[](j + 1);
                array->operator[](j + 1) = temp;
            }
        }
    }
}


template<typename container_t>
QVector<quint64> KMath::customContainerIndices(container_t container) const {
    if(container.size() <= 0)
        return QVector<quint64>();
    int currentIndex = 0;
    auto currentValue = container[currentIndex];
    QVector<quint64> result;

    typedef typename std::remove_reference<decltype (currentValue)>::type item_t;

    result.push_back(currentIndex);
    for (int i = 1; i < container.size(); ++i) {
        if(!KCompareEngine<item_t>::compare(currentValue, container[i])) {
            ++currentIndex;
            currentValue = container[i];
        }
        result.push_back(currentIndex);
    }
    return result;
}


#endif // KMATH_H
