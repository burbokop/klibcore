#ifndef KAUDIODEVICE_H
#define KAUDIODEVICE_H

#include <QAudioFormat>
#include <QIODevice>
#include <src/kmacro.h>
#include <src/math/processors/ksignalprocessor.h>

class KAudioDevice : public QIODevice, public KSignalProcessor {
    Q_OBJECT
    QAudioFormat m_format;

    QAudioFormat generateFormat();
public:
    KAudioDevice(QObject *parent = nullptr);
    QAudioFormat format() const;

    // QIODevice interface
protected:
    qint64 readData(char *data, qint64 len) override;
    qint64 writeData(const char *data, qint64 len) override;
};









#endif // KAUDIODEVICE_H
