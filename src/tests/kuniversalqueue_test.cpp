#include "kuniversalqueue_test.h"

#include <src/experimental/universalqueue/kuniversalqueue.h>
#include <QTest>

KUniversalQueue_Test::KUniversalQueue_Test(QObject *parent) : QObject(parent) {

}

struct TestStruct {
    int i = 0;
    double j = 0;
    friend bool operator ==(const TestStruct s1, const TestStruct s2) {
        return s1.i == s2.i && s1.j == s2.j;
    };
};


void KUniversalQueue_Test::push_pop_test() {
    KUniversalQueue queue;


    queue.enqueue<int>(4);
    queue.enqueue<TestStruct>({ 3, 6.5 });
    TestStruct s{ 3, 6.5 };


    QCOMPARE(queue.dequeue<int>(), 4);
    QCOMPARE(queue.dequeue<TestStruct>(), s);
}
