#ifndef KUNIVERSALQUEUE_TEST_H
#define KUNIVERSALQUEUE_TEST_H

#include <QObject>

class KUniversalQueue_Test : public QObject {
    Q_OBJECT
public:
    explicit KUniversalQueue_Test(QObject *parent = nullptr);

signals:

private slots:
    void push_pop_test();
};

#endif // KUNIVERSALQUEUE_TEST_H
