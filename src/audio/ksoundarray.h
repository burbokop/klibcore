#ifndef KSOUNDARRAY_H
#define KSOUNDARRAY_H

#include "ksound.h"
#include <QVector>



class KSoundArray : public KSound {
    Q_OBJECT
    QList<KSound*> m_sounds;
public:
    KSoundArray(bool play = false, QObject *parent = nullptr);
    void addSound(QVector<KSound*> *vectorSound);
    void addSound(KSound *sound);
    int size();
    void removeSound(KSound *sound);
    QList<KSound *> sounds() const;
signals:
    void soundAdded(KSound *sound);
    void soundRemoved(KSound *sound);
};

#endif // KSOUNDARRAY_H
