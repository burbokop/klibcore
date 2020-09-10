#include "ksoundarray.h"

QList<KSound *> KSoundArray::sounds() const {
    return m_sounds;
}

KSoundArray::KSoundArray(bool play, QObject *parent) : KSound(play, parent) {
    connect(this, &KSound::sampleRateChanged, this, [this](qint64 value){
        for(KSound *sound : m_sounds) {
            sound->setSampleRate(value);
        }
    });
}

void KSoundArray::addSound(QVector<KSound *> *vectorSound)
{
    for(auto sound = vectorSound->constBegin(); sound < vectorSound->constEnd(); ++sound)
    {
        (*sound)->setParent(this);
        m_sounds.push_back(*sound);
        emit soundAdded(*sound);
    }
}

void KSoundArray::addSound(KSound *sound) {
    sound->setParent(this);
    m_sounds.push_back(sound);
    emit soundAdded(sound);
}

int KSoundArray::size()
{
    return m_sounds.size();
}

void KSoundArray::removeSound(KSound *sound) {
    sound->setParent(nullptr);
    m_sounds.removeOne(sound);
    emit soundRemoved(sound);
}
