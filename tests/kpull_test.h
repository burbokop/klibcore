#ifndef KPULL_TEST_H
#define KPULL_TEST_H

#include <src/kmacro.h>

class UniqId : public QObject {
    Q_OBJECT
    static inline int nextId = 0;
    K_READONLY_PROPERTY(int, id, id, setId, idChanged, 0)
public:
    UniqId(QObject *parent = nullptr);
};



class KPull_Test : public QObject
{
    Q_OBJECT
public:
    explicit KPull_Test(QObject *parent = nullptr);

    QList<int> lockedIndices(const std::map<UniqId*, bool> &data);
    QList<int> indices(QList<UniqId*> data);
private slots:

    void test();

signals:

};

#endif // KPULL_TEST_H
