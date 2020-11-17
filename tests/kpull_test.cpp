#include "kpull_test.h"

#include <QtDebug>

#include <src/memcontrol/kpull.h>
KPull_Test::KPull_Test(QObject *parent) : QObject(parent)
{

}

QList<int> KPull_Test::lockedIndices(const std::map<UniqId *, bool> &data) {
    QList<int> result;
    for(auto m : data) {
        if(m.second)
            result.push_back(m.first->id());
    }
    return result;
}

QList<int> KPull_Test::indices(QList<UniqId*> data) {
    QList<int> result;
    for(auto m : data) {
        result.push_back(m->id());
    }
    return result;
}

void KPull_Test::test() {

    KPull<QString, UniqId> pull;
    pull.registerType<UniqId>();
    KType<UniqId> className;

    auto obj1 = pull.takeObject(className);
    auto obj2 = pull.takeObject(className);
    auto obj3 = pull.takeObject(className);

    qDebug() << obj1->id() << obj2->id() << obj3->id() << "locked:";

    qDebug() << "pull.returnObject(obj1)" << pull.returnObject(obj1) << "locked:";
    qDebug() << "pull.returnObject(obj1)" << pull.returnObject(obj1) << "locked:";


    auto obj4 = pull.takeObject(className);
    auto obj5 = pull.takeObject(className);
    auto obj6 = pull.takeObject(className);
    qDebug() << obj4->id() << obj5->id() << obj6->id() << "locked:";


    qDebug() << "pull.returnObject(obj2)" << pull.returnObject(obj2) << "locked:";
    qDebug() << "pull.returnObject(obj3)" << pull.returnObject(obj3) << "locked:";


    pull.clearAvailable();
    qDebug() << obj4->id() << obj5->id() << obj6->id() << "locked:";
    pull.termainteAll();
}

UniqId::UniqId(QObject *parent) : QObject(parent) {
    setId(nextId++);
}
