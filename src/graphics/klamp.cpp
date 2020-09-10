#include "klamp.h"
#include "klamprectangle.h"

KLamp::KLamp(QQuickItem *parent) : QQuickItem(parent) {
    setWidth(30);
    setHeight(30);

    qmlLoader->load("import QtQuick 2.0; Rectangle { anchors.fill: parent }", QUrl("rect"));
    qmlLoader->load("import QtQuick 2.0; Text { anchors.centerIn: parent }", QUrl("text"));

    connect(qmlLoader, &KQmlLoader::loadingCompleated, this, [this](QQuickItem *item, auto url) {
        if(url == QUrl("rect")) {
            item->setProperty("color", backgroundColor());
            connect(this, &KLamp::backgroundColorChanged, item, [item](auto value) {
                item->setProperty("color", value);
            });
            item->setZ(-1);
        } else if(url == QUrl("text")) {
            item->setProperty("color", textColor());
            connect(this, &KLamp::textColorChanged, item, [item](auto value) {
                item->setProperty("color", value);
            });
            item->setProperty("text", text());
            connect(this, &KLamp::textChanged, item, [item](auto value) {
                item->setProperty("text", value);
            });
            item->setZ(1);
        }
    });

    auto lamp = new KLampRectangle(this);
    afterShining()->setContentPaintedItem(lamp);
    afterShining()->setZ(0);
    connect(this, &KLamp::ledColorChanged, lamp, &KLampRectangle::setLedColor);
    connect(this, &KLamp::stateChanged, lamp, &KLampRectangle::setState);

    lamp->setLedColor(ledColor());
    lamp->setState(state());

    connect(this, &KLamp::widthChanged, this, [this]() { afterShining()->setWidth(width()); });
    connect(this, &KLamp::heightChanged, this, [this]() { afterShining()->setHeight(height()); });
    afterShining()->setWidth(width());
    afterShining()->setHeight(height());
}
