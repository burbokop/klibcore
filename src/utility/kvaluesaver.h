#ifndef KVALUESAVER_H
#define KVALUESAVER_H

#include <src/kmacro.h>

class KValueSaver : public QObject {
    Q_OBJECT
    K_OBJECT
    K_QML_TYPE(KValueSaver)
    K_AUTO_PROPERTY(QVariant, value, value, setValue, valueChanged, QVariant())
    QString m_path;
public:
    explicit KValueSaver(QObject *parent = nullptr);
public slots:
    bool bindToFile(QString path, bool convertToAbsolutePath = true);

signals:

};

#endif // KVALUESAVER_H
