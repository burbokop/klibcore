#include "ksoundchain.h"


qint64 KSoundChain::interval() const {
    return m_interval;
}

void KSoundChain::setInterval(const qint64 &interval) {
    m_interval = interval;
}

void KSoundChain::switchSound() {
    if(currentSound) {
        int index = sounds().indexOf(currentSound);
        if(++index < sounds().size()) {
            currentSound = sounds().at(index);
        } else {
            currentSound = nullptr;
        }
    }
}

KSoundChain::KSoundChain(bool play, QObject *parent) : KSoundArray(play, parent) {
    stepTimer.start();
    //stepTimer.stop();
    connect(this, &KSoundArray::soundAdded, this, [this](KSound*) {
        if(sounds().size() == 1) {
            reset();
        }
    });
}

void KSoundChain::reset() {
    if(sounds().size() > 0) {
        currentSound = sounds().first();
    }
}

double KSoundChain::signal(qint64 index) {
    if(play()) {
        //stepTimer.resume();
    } else {
        //stepTimer.stop();
    }


    if(stepTimer.elapsed() > interval()) {
        switchSound();
        stepTimer.restart();
    }

    if(currentSound) {
        return currentSound->volume(index);
    }
    return 0;
}
