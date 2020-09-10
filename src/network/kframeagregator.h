#ifndef KFRAMEAGREGATOR_H
#define KFRAMEAGREGATOR_H

#include <QAbstractSocket>
#include <QObject>

class KFrameAgregator : public QObject {
    Q_OBJECT
public:
    enum { ChecksumError = 23 };
    KFrameAgregator(QObject *parent = nullptr);
    KFrameAgregator(QAbstractSocket *parent);
    bool hasFrameBuffered();
    QByteArray readFrame();
    void writeFrame(QByteArray data);
    QAbstractSocket *socket() const;
    void setSocket(QAbstractSocket *socket);
private:
    QByteArray buffer;
    QByteArray uncovered;
    QAbstractSocket *m_socket;
    QHash<QByteArray, QByteArray> hash;
    void recieveFrameData();
    QByteArray cover(QByteArray data);
    QByteArray uncover(QByteArray frame);
};

#endif // KFRAMEAGREGATOR_H
