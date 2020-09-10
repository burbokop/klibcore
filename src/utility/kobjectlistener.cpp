#include "kobjectlistener.h"

KObjectListener::KObjectListener(QObject *parent) : QObject(parent) {}

void KObjectListener::onPropertyNotify() {
    auto property = QObject::sender()->metaObject()->property(properties[QObject::sender()][QObject::senderSignalIndex()]);
    emit propertyEvent(QObject::sender()->objectName(), property.name(), property.read(QObject::sender()));
}

bool KObjectListener::linkProperty(QObject *obj, const QMetaProperty &prop, QString slot) {
    auto signal = prop.notifySignal();
    auto meta = this->metaObject();
    auto slotIndex = meta->indexOfMethod(slot.toStdString().c_str());
    if(slotIndex >= 0) {
        properties[obj][signal.methodIndex()] = prop.propertyIndex();
        return connect(obj, signal, this, meta->method(slotIndex));
    }
    return false;
}

bool KObjectListener::listen(QObject *object) {
    auto meta = object->metaObject();
    bool connectedAnything = false;
    for(auto i = 0, size = meta->propertyCount(); i < size; ++i) {
        if(linkProperty(object, meta->property(i), "onPropertyNotify()"))
            connectedAnything = true;
    }
    return connectedAnything;
}
