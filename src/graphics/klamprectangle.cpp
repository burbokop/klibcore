#include "klamprectangle.h"

#include <QPainter>

KLampRectangle::KLampRectangle(QQuickItem *parent) : KPaintedItem(parent) {
    connect(this, &KLampRectangle::stateChanged, this, [this](bool s) {
        if(s)
            highState = true;

        if(autoUpdateEnabled())
            update();        
    });
}

void KLampRectangle::paint(QPainter *painter) {
    if(painter->isActive() && highState) {
        painter->setPen(ledColor());
        painter->setBrush(ledColor());
        painter->drawRect(boundingRect());

        if(!state())
            highState = false;
    }
}
