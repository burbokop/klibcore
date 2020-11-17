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
