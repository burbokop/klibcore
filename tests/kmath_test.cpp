#include "kmath_test.h"

#include <QTest>
#include <src/math/kmath.h>

KMath_Test::KMath_Test(QObject *parent) : QObject(parent) {

}

void KMath_Test::bubbleSort_test() {
    auto math = KMath::instance();
    QCOMPARE(math->bubbleSort(QVector<double>{ 0, 4, 3, 2, 4 }), (QVector<double>{ 0, 2, 3, 4, 4 }));
    QCOMPARE(math->bubbleSort(QVector<double>{ 1, 2, 3, 4, 5 }), (QVector<double>{ 1, 2, 3, 4, 5 }));
    QCOMPARE(math->bubbleSort(QVector<double>{ 5, 4, 3, 2, 1 }), (QVector<double>{ 1, 2, 3, 4, 5 }));
    QCOMPARE(math->bubbleSort(QVector<double>{ 9, 4, 2, 8, 0 }), (QVector<double>{ 0, 2, 4, 8, 9 }));
    QCOMPARE(math->bubbleSort(QVector<double>{ 11, 22, 33, 44, 11 }), (QVector<double>{ 11, 11, 22, 33, 44 }));
    QCOMPARE(math->bubbleSort(QVector<double>{ 0.5, 0.24, 1.3, 0.897, 0.1 }), (QVector<double>{ 0.1, 0.24, 0.5, 0.897, 1.3 }));
}

void KMath_Test::vectorIndices_test() {
    auto math = KMath::instance();
    QCOMPARE(math->vectorIndices(QVector<double>{ 0, 2, 3, 4, 4 }), (QVector<quint64>{ 0, 1, 2, 3, 3 }));
    QCOMPARE(math->vectorIndices(QVector<double>{ 0, 0, 0, 111.1, 111.1 }), (QVector<quint64>{ 0, 0, 0, 1, 1 }));
    QCOMPARE(math->vectorIndices(QVector<double>{ 11, 11, 22, 33, 44 }), (QVector<quint64>{ 0, 0, 1, 2, 3 }));
    QCOMPARE(math->vectorIndices(QVector<double>{ 1, 2, 3, 4, 5 }), (QVector<quint64>{ 0, 1, 2, 3, 4 }));
    QCOMPARE(math->vectorIndices(QVector<double>{ 0.1, 0.24, 0.5, 0.897, 1.3 }), (QVector<quint64>{ 0, 1, 2, 3, 4 }));
}

void KMath_Test::limitValue_test() {
    auto math = KMath::instance();
    QCOMPARE(math->limitValue(3, 0, 4), 3);
    QCOMPARE(math->limitValue(3, 0, 2), 2);
    QCOMPARE(math->limitValue(3, -2, -1), -1);
    QCOMPARE(math->limitValue(-10, 0, 4), 0);
}

void KMath_Test::limitedMap_test() {
    auto math = KMath::instance();
    QCOMPARE(math->limitedMap(3, 0, 4, 0, 8), 6);
    QCOMPARE(math->limitedMap(3, 0, 2, 0, 8), 8);
    QCOMPARE(math->limitedMap(3, -2, -1, 0, 8), 8);
    QCOMPARE(math->limitedMap(-10, 0, 4, 0, 8), 0);
}
