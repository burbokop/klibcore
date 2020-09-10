#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>
#include <QTest>
#include <QTimer>

#include <src/tests/kadditional_test.h>
#include <src/tests/kflexiblemodel_test.h>
#include <src/tests/kmath_test.h>
#include <src/tests/kpull_test.h>
#include <src/tests/kuniversalqueue_test.h>
#include <src/utility/kmemorydiagnosticservice.h>
#include <iostream>





#ifndef KLIBCORE_USE_LIBRARY

int main(int argc, char *argv[]) {

    auto vec = __KMeta::classNames();
    for(auto v : vec) {
        std::cout << v << "\n";
    }
    qmlRegisterType<QObject>("KLib", 1, 0, "Null");



    QGuiApplication app(argc, argv);
    QTest::qExec(new KMath_Test, argc, argv);
    QTest::qExec(new KAdditional_Test, argc, argv);
    QTest::qExec(new KUniversalQueue_Test, argc, argv);
    QTest::qExec(new KFlexibleModel_Test, argc, argv);
    QTest::qExec(new KPull_Test, argc, argv);

    QQuickView view;
    view.setSource(QUrl("qrc:/klibmain.qml"));
    view.show();

    return app.exec();
}
#endif
