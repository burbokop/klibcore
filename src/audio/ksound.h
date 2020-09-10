#ifndef KSOUND_H
#define KSOUND_H

#include <QObject>


class KSound : public QObject {
    Q_OBJECT
    bool m_play = false;
    qint64 m_sampleRate = 0;
    double m_amplitude = 1;
    static inline int m_instanceCount = 0;
protected:
    virtual double signal(qint64 index) = 0;


public:
    explicit KSound(bool play = false, QObject *parent = nullptr);

    inline double volume(qint64 index);

    bool play() const;
    void setPlay(bool play);
    qint64 sampleRate() const;
    void setSampleRate(const qint64 &sampleRate);
    double amplitude() const;
    void setAmplitude(double amplitude);

    virtual ~KSound() { m_instanceCount--; }
    static int instanceCount();

signals:
    void playChanged(bool);
    void sampleRateChanged(qint64);
public slots:


    protected:
    virtual void overrideSetPlay(){};
};

double KSound::volume(qint64 index) {
    if(m_play)
        return signal(index) * amplitude();
    return 0;
}

#endif // KSOUND_H
