#ifndef KLAMPRECTANGLE_H
#define KLAMPRECTANGLE_H

#include "kpainteditem.h"
#include <src/kmacro.h>


/**
 * @brief The KLampRectangle class is simple squere whitch can change color and is compatible with KAfterShiningMonitor
 * @details
 * \n
 * PROPERTIES:
 *
 * | modyfier | type   | name     | description                                 |
 * | -------- | ------ | -------- | ------------------------------------------- |
 * | writable | bool   | state    | this property means if led is on            |
 * | writable | QColor | ledColor | color of enabled stete, instead transperent |
 *
 */
class KLampRectangle : public KPaintedItem {
    Q_OBJECT
    K_QML_TYPE(KLampRectangle)
    K_AUTO_PROPERTY(bool, state, state, setState, stateChanged, false)
    K_AUTO_PROPERTY(QColor, ledColor, ledColor, setLedColor, ledColorChanged, Qt::yellow)

    bool highState = false;
public:
    KLampRectangle(QQuickItem *parent = nullptr);

    // QQuickPaintedItem interface
public:
    virtual void paint(QPainter *painter) override;
};

#endif // KLAMPRECTANGLE_H
