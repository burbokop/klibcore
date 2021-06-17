#include "kadditional_test.h"
#include <QTest>
#include <qaudiooutput.h>
#include <src/kadditional.h>

KAdditional_Test::KAdditional_Test(QObject *parent) : QObject(parent) {

}

void KAdditional_Test::constrainPath_test() {
    QCOMPARE(KAdditional::constrainPath("/home/user/Documents/../"), "/home/user");
    QCOMPARE(KAdditional::constrainPath("/home/user/Documents/../../source"), "/home/source");
    QCOMPARE(KAdditional::constrainPath("/home/./gogadoda"), "/home/gogadoda");
    QCOMPARE(KAdditional::constrainPath("/home/user/file.png"), "/home/user/file.png");
    QCOMPARE(KAdditional::constrainPath("/home/user/"), "/home/user");
    QCOMPARE(KAdditional::constrainPath("/home/user/Documents/../file.png"), "/home/user/file.png");
}

void KAdditional_Test::groupedOn_test() {
    {
        QVector<int> vec = { 0, 1, 2, 3 };
        auto res = KAdditional::groupedOn(vec, 3);
        QCOMPARE(res.size(), 3);
        size_t sum = 0;
        for(const auto& i : res) {
            QCOMPARE(i.size() > 0, true);
            QCOMPARE(i.size() < 3, true);
            qDebug() << "0 group:" << i;
            sum += i.size();
        }
        QCOMPARE(sum, 4);
    }

    {
        QVector<int> vec = { 0, 1, 2, 3 };
        auto res = KAdditional::groupedOn(vec, 2);
        QCOMPARE(res.size(), 2);
        size_t sum = 0;
        for(const auto& i : res) {
            QCOMPARE(i.size() > 0, true);
            QCOMPARE(i.size() < 3, true);
            qDebug() << "1 group:" << i;
            sum += i.size();
        }
        QCOMPARE(sum, 4);
    }
}
