#ifndef KMATH_TEST_H
#define KMATH_TEST_H

#include <QObject>

class KMath_Test : public QObject {
    Q_OBJECT
public:
    explicit KMath_Test(QObject *parent = nullptr);

private slots:
    void bubbleSort_test();
    void vectorIndices_test();
    void limitValue_test();
    void limitedMap_test();
signals:

};

#endif // KMATH_TEST_H
