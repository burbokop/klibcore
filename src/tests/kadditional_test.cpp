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
