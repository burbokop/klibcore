#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>
#include <QTest>
#include <QTimer>

#include "kadditional_test.h"
#include "kflexiblemodel_test.h"
#include "kmath_test.h"
#include "kpull_test.h"
#include "kuniversalqueue_test.h"
#include <src/utility/kmemorydiagnosticservice.h>
#include <iostream>


int main(int argc, char *argv[]) {
    int code = 0;
    code = QTest::qExec(new KMath_Test, argc, argv);
    if (code != 0)
        return code;
    code = QTest::qExec(new KAdditional_Test, argc, argv);
    if (code != 0)
        return code;
    code = QTest::qExec(new KUniversalQueue_Test, argc, argv);
    if (code != 0)
        return code;
    code = QTest::qExec(new KFlexibleModel_Test, argc, argv);
    if (code != 0)
        return code;
    code = QTest::qExec(new KPull_Test, argc, argv);
}
