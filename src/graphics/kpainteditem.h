#ifndef KPAINTEDITEM_H
#define KPAINTEDITEM_H

#include <QQuickPaintedItem>
#include <src/kmacro.h>

class KPaintedItem : public QQuickPaintedItem {
    Q_OBJECT
    K_QML_INTERFACE(KPaintedItem)
    K_AUTO_PROPERTY(bool, autoUpdateEnabled, autoUpdateEnabled, setAutoUpdateEnabled, autoUpdateEnabledChanged, true)
public:
    KPaintedItem(QQuickItem *parent = nullptr);
};

#endif // KPAINTEDITEM_H
