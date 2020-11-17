#include "kflexiblemodel_test.h"

#include <QVariantMap>
#include <QTest>

KFlexibleModel_Test::KFlexibleModel_Test(QObject *parent) : QObject(parent)
{
    //cppTest();
}

void KFlexibleModel_Test::cppTest()
{
    auto flex = flexibleModel();
    flex->addRole("Test1");
    flex->addRoles({"Test2", "Test3", "Test1"});
    flex->push_back({31, 3.2, 33.0});
    flex->push_front({11, 12.0, 1.3});
    flex->push_front({{"Test1", 0.1}, {"Test2", 0.20}});
    flex->push_back({{"Test3", 4.1}, {"Test2", 42}});
    flex->setLineData(QVariantMap{{"Test3", 0.3}}, 0);
    flex->setLineData({40}, 3);
    flex->setLineData({71, 72, 73}, 6);
    flex->insert(4, QVariantMap{{"Test3", 6.3}, {"Test2", "62"}, {"Test3", "63"}, {"Test1", "6.1"}});
    flex->insert(4, {5, 51, 5.2});
    flex->remove(7);
    QVariant list = flex->serialize();

    KFlexibleModel flex1;
    flex1 = *flex;
    flex1.addRole("Test4");
    flex1.deserialize(list, false, true);

    KFlexibleModel flex2;
    flex2.deserialize(list);
    flex1.deserialize(flex2.serialize(), false, true);

    QCOMPARE(flex2.indexOf("62"), 5);
    QCOMPARE(flex2.indexOf("62", "Test2"), 5);
    QCOMPARE(flex2.indexOf("64"), -1);



    auto flex4 = flex;
    QCOMPARE((flex4 == flex), true);

    flex4->setLineData({"test", "test1"});
    flex4->setLineData({"test2", "test"}, 3);
    flex4->setLineData({"test", "test2"}, 5);

    auto er = flex4->indicesOf({{"Test1", "test"}, {"Test2", "test1"}});

    QCOMPARE(er, QVariantList({0}));
    QCOMPARE(flex4->indicesOf({{"Test1", "test"}, {"Test2", "test1"}}, false), QVariantList({0, 5}));
    QCOMPARE(flex4->indicesOf({"test", "test1"}), QVariantList({0}));
    QCOMPARE(flex4->indicesOf({"test", "test1"}, false), QVariantList({0, 3, 5}));
    QCOMPARE(flex4->indicesOf({"test", "test1"}, "Test1"), QVariantList({0}));
    QCOMPARE(flex4->contains({{"Test1", "test"}, {"Test2", "test1"}}), true);
    QCOMPARE(flex4->contains({{"Test1", "test"}, {"Test2", "test0"}}), false);
}

QString KFlexibleModel_Test::qmlTest() {
    return QString();
}

bool KFlexibleModel_Test::checkResult() {
    return false;
}
