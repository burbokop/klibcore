#include "kmodulehandler.h"

#include <QQmlEngine>
#include <QThread>
#include <QTimer>
#include <QWidget>
#include <QtDebug>

KModuleHandler::KModuleHandler(QObject *parent) : QObject(parent) {
    connect(this, &KModuleHandler::modeChanged, this, &KModuleHandler::applyMode, Qt::ConnectionType::QueuedConnection);
}

void KModuleHandler::initObject(QObject *obj) {
    auto widget = qobject_cast<QWidget*>(obj);
    if(widget) {
        widget->show();
    } else {
        obj->setParent(this);
        auto thread = qobject_cast<QThread*>(obj);
        if(thread) {
            thread->start();
        }
    }
}

void KModuleHandler::deinitObject(QObject *obj) {
    if(auto t = qobject_cast<QThread*>(obj)) {
        t->terminate();
        t->wait(1000);
    }
}

void KModuleHandler::applyMode(QString mode) {
    for(auto i : m_instances) {
        deinitObject(i);
        if(storeModes[i] == Pull) {
            pull.returnObject(i);
        } else if(storeModes[i] == Reincarnation) {
            delete i;
        } else {
            qWarning() << "KModuleHandler: store mode not specified. can't delocate object.";
        }
    }
    m_instances.clear();

    if(modes.contains(mode)) {
        auto newMode = modes[mode];
        for(auto m : newMode) {
            QObject *inst = nullptr;
            if(m.storeMode == Pull) {
                inst = pull.takeObject(m.className);
                storeModes[inst] = Pull;
            } else if(m.storeMode == Reincarnation) {
                inst = factory.create(m.className);
                storeModes[inst] = Reincarnation;
            }

            if(inst) {
                initObject(inst);
                m_instances.push_back(inst);
                emit objectInstantiated(inst);
            }
        }
    }

    instancesChanged(instances());
}

QObject *KModuleHandler::firstOfName(QString name) {
    for(auto i : m_instances) {
        if(i->objectName() == name)
            return i;
    }
    return nullptr;
}
