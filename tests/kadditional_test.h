#ifndef KADDITIONAL_TEST_H
#define KADDITIONAL_TEST_H

#include <QObject>

class KAdditional_Test : public QObject
{
    Q_OBJECT
public:
    explicit KAdditional_Test(QObject *parent = nullptr);

private slots:
    void constrainPath_test();

    void groupedOn_test();

signals:

};

#endif // KADDITIONAL_TEST_H
