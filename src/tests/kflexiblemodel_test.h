#ifndef KFLEXIBLEMODEL_TEST_H
#define KFLEXIBLEMODEL_TEST_H

#include <QObject>
#include <src/kmacro.h>
#include <src/models/kflexiblemodel.h>

class KFlexibleModel_Test : public QObject
{
    Q_OBJECT
    K_QML_TYPE(KFlexibleModel_Test)
    K_READONLY_PROPERTY(KFlexibleModel *, flexibleModel, flexibleModel, setFlexibleModel, flexibleModelChanged, new KFlexibleModel(this))
public:
    explicit KFlexibleModel_Test(QObject *parent = nullptr);

private slots:
    void cppTest();


public slots:
    QString qmlTest();
    bool checkResult();

signals:

};

#endif // KFLEXIBLEMODEL_TEST_H
